'use strict';
const { PomeloLua } = require('bindings')('pomelolua');

const example = new PomeloLua(11);
console.time('aaaaa')
console.log(example.doString(`result = 77; message="fff"`));
console.timeLog('aaaaa')

const format = function(bytes) { 
    return (bytes/1024/1024).toFixed(2)+'MB'; 
};

setInterval(() => {
    example.doString(`result = 88;`);
    const r = example.doString(`result = true;`);
    console.log(r);
}, 1);

setInterval(() => {
    const mem = process.memoryUsage();
    console.log('Process: heapTotal '+format(mem.heapTotal) + ' heapUsed ' + format(mem.heapUsed) + ' rss ' + format(mem.rss));
}, 5000)


console.timeLog('aaaaa')
// Unchanged. It prints 19