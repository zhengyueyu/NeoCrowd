const express = require('express');
require('express-async-errors');
const fileUpload = require('express-fileupload');
const app = express();
const bodyParser = require('body-parser');
const ref = require('ref');
const struct = require('ref-struct')
const ffi = require('ffi');

const rectStruct = struct({
    id: 'int',
    confidence: 'double',
    xLeftBottom: 'int',
    yLeftBottom: 'int',
    xRightTop: 'int',
    yRightTop: 'int'
});
const rectStructPtr = ref.refType(rectStruct);
const outputStruct = struct({
    output: rectStructPtr,
    count: 'int',
    image: 'string'
});
const outputStructPtr = ref.refType(outputStruct);

const libt = ffi.Library("./libneo_demo.so", {
    init_model: ['void', ['double']],
    static_exec: [outputStructPtr, ['string', 'bool', 'string']],
    output_free: ['void', [outputStructPtr]]
});

app.use(bodyParser.urlencoded({
    extended: true,
    limit: '50mb'
}));
app.use(fileUpload());
app.use(express.static('public'));

app.post("/", async function (req, res) {
    if (!req.body.image) {
        res.status(400).send();
        return;
    }
    //console.log(req.body);
    const image_buf = Buffer.from(req.body.image);
    const roi_buf = req.body.area ? Buffer.from(req.body.area) : ref.NULL;
    const pre = Date.now();
    const express_res = res;
    libt.static_exec.async(image_buf, true, roi_buf, function (err, res) {
        if (err) throw err;
        const outputPtr = res;
        const time_ms = Date.now() - pre;
        const output = ref.deref(outputPtr);
        const count = output.count;
        const cAreaArr = ref.reinterpret(output.output, count * rectStruct.size, 0);

        let areaArr = [];
        for (let i = 0; i < count; ++i) {
            const item = ref.get(cAreaArr, i * rectStruct.size, rectStruct);
            areaArr.push({
                id: item.id,
                confidence: item.confidence,
                location: {
                    xLeftBottom: item.xLeftBottom,
                    yLeftBottom: item.yLeftBottom,
                    xRightTop: item.xRightTop,
                    yRightTop: item.yRightTop
                }
            });
        }

        let retObj = {
            person_num: count,
            person_info: areaArr,
            time_consuming_ms: time_ms
        }
        retObj.image = output.image;
        libt.output_free.async(outputPtr, function(err, res) {
            if (err) throw err;
        });
        express_res.send(retObj);
    });
});

app.post("/tracker", async function (req, res) {
    console.log(req.files);
    res.send({ name: req.files.video.name, size: req.files.video.size });  // temp
});

libt.init_model(0.3);  // 概率阈值设定
app.listen(8080, () => console.log("Run Success On 8080!"));