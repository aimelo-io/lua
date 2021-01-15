'use strict';
const { PomeloLua } = require('bindings')('pomelolua');

const example = new PomeloLua(11);
console.time('aaaaa')
console.log(example.doString(`result = 77; message="fff"`));
console.timeLog('aaaaa')
for (let i = 0; i < 10000; i++ ) {
    example.doString(`result=${i}`)
}

console.log(example.doString(`result = 88;`));

console.timeLog('aaaaa')
// Unchanged. It prints 19