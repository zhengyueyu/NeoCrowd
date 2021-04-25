import argparse
import io
import time

from utils.datasets import *
from utils.utils import *

from reid.data import make_data_loader
from reid.data.transforms import build_transforms
from reid.modeling import build_model
from reid.config import cfg as reidCfg
import numpy as np
import cv2

class ReidRunner:

    def __init__(self):
        self.device = torch_utils.select_device(force_cpu=False)
        torch.backends.cudnn.benchmark = False

        # Initialize the reid model
        reidCfg.DATASETS.ROOT_DIR = ('./query/')
        query_loader, num_query = make_data_loader(reidCfg)
        self.reidModel = build_model(reidCfg, num_classes=10126)
        self.reidModel.load_param(reidCfg.TEST.WEIGHT)
        self.reidModel.to(self.device).eval()

        self.query_feats = []
        self.query_pids = []
        self.query_camid = []

        for i, batch in enumerate(query_loader):
            with torch.no_grad():
                img, pid, camid = batch
                img = img.to(self.device)
                feat = self.reidModel(img)
                self.query_feats.append(feat)
                self.query_pids.extend(np.asarray(pid))
                self.query_camid.extend(np.asarray(camid))

        self.query_feats = torch.cat(self.query_feats, dim=0)
        self.query_feats = torch.nn.functional.normalize(self.query_feats, dim=1, p=2)
        print(self.query_feats)
        print("The query feature is normalized")

    def detect(self,
               images,
               stamp,
               dist_thres=1.0):

        camid = 0  #这里定义camid
        # start re-id
        crop_img = build_transforms(reidCfg)(images).unsqueeze(0)
        gallery_img = []
        gallery_img.append(crop_img)
        if gallery_img:
            gallery_img = torch.cat(gallery_img, dim=0)
            gallery_img = gallery_img.to(self.device)
            gallery_feats = self.reidModel(gallery_img)
            print("The gallery feature is normalized")
            gallery_feats = torch.nn.functional.normalize(gallery_feats, dim=1, p=2)

            for i, m_query_feat in enumerate(self.query_feats):
                m_query_feat = torch.reshape(m_query_feat, (1, 2048))
                m, n = m_query_feat.shape[0], gallery_feats.shape[0]
                distmat = torch.pow(m_query_feat, 2).sum(dim=1, keepdim=True).expand(m, n) + \
                         torch.pow(gallery_feats, 2).sum(dim=1, keepdim=True).expand(n, m).t()
                distmat.addmm_(1, -2, m_query_feat, gallery_feats.t())
                distmat = distmat.cpu().numpy()
                distmat = distmat.sum(axis=0) / len(m_query_feat)
                index = distmat.argmin()
                print('stamp:', stamp, '\tpid:', self.query_pids[i], '\tdismat:', distmat[index])
                if distmat[index] < dist_thres:
                    return self.query_pids[i]

            # 如果query中没有要找的目标
            #Step 1:找到最大值，存储图片
            if len(self.query_pids) != 0:
                pids_copy = self.query_pids[:]  #copy一下pids列表用来寻找最大值，以便分配新id
                pids_copy.sort()
                x = pids_copy[-1] + 1
            else:
                x = 0
            x_str = str(x)
            path = './query/' + x_str.rjust(4, '0') + '_c1s1_0_0_' + str(time.time()) + '.jpg'
            images.save(path)

            #Step 2:自学习
            with torch.no_grad():

                #提取特征并normalized
                new_id_img = build_transforms(reidCfg)(images).unsqueeze(0)
                new_id_imgs = []
                new_id_imgs.append(new_id_img)
                new_id_imgs = torch.cat(new_id_imgs, dim=0)
                new_id_imgs = new_id_imgs.to(self.device)
                new_id_feats = self.reidModel(new_id_imgs)
                new_id_feats = torch.nn.functional.normalize(new_id_feats, dim=1, p=2)
                print("The gallery feature is normalized")

                #加入总的特征矩阵
                self.query_feats = torch.cat((self.query_feats, new_id_feats), 0)
                temp = []
                temp.append(x)
                self.query_pids.extend(np.asarray(temp))
            return x