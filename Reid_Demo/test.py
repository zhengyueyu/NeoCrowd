from utils.utils import *
from reid.data import make_data_loader
from reid.data.transforms import build_transforms
from reid.modeling import build_model
from reid.config import cfg as reidCfg
import numpy as np

device = torch_utils.select_device(force_cpu=False)
torch.backends.cudnn.benchmark = False
reidCfg.DATASETS.ROOT_DIR = ('./query/')
query_loader, num_query = make_data_loader(reidCfg)
reidModel = build_model(reidCfg, num_classes=10126)
reidModel.load_param(reidCfg.TEST.WEIGHT)
reidModel.to(device).eval()


img = Image.open('./query/0001_c1s1_0_146.jpg')
crop_img = build_transforms(reidCfg)(img).unsqueeze(0)
gallery_img = []
gallery_img.append(crop_img)
gallery_img = torch.cat(gallery_img, dim=0)
gallery_img = gallery_img.to(device)
gallery_feats = reidModel(gallery_img)
print("The gallery feature is normalized")
gallery_feats = torch.nn.functional.normalize(gallery_feats, dim=1, p=2)
print(gallery_feats)
