import argparse
import io
import time

from runreid import ReidRunner
import json
from utils.utils import *
from reid.data import make_data_loader
from reid.data.transforms import build_transforms
from reid.modeling import build_model
from reid.config import cfg as reidCfg
import numpy as np
import tornado.web
import tornado.options
from tornado.options import define, options
from tornado.web import RequestHandler
import tornado.httpserver
import tornado.ioloop
import base64


define('port', default=8080, help='run port', type=int)


class ReidHandler(RequestHandler):

    def initialize(self, reidRunner):
        self.reid = reidRunner

    def get(self):
        self.write('Use the post method to post your json.')
        return

    def post(self):
        print(self.request.remote_ip)
        parse_data = tornado.escape.json_decode(self.request.body)
        if parse_data["stamp"] and parse_data["image"]:
            stamp = parse_data["stamp"]
            image = parse_data["image"]
            image_decoded = base64.b64decode(image)
            image = io.BytesIO(image_decoded)
            img = Image.open(image)
            with torch.no_grad():
                id = self.reid.detect(img, stamp=stamp)
            json_text = {'stamp':stamp, 'id':str(id)}
            print('webserver:', json_text)
            json = tornado.escape.json_encode(json_text)
            self.write(json)

            return



if __name__ == '__main__':
    print('服务启动')
    rr = ReidRunner()
    print('Reid初始化完成')
    app = tornado.web.Application([
        (r'/', ReidHandler, dict(reidRunner=rr))
    ])
    tornado.options.parse_command_line()
    print('监听端口: ', options.port)
    server = tornado.httpserver.HTTPServer(app)
    server.listen(options.port)
    tornado.ioloop.IOLoop.instance().start()
