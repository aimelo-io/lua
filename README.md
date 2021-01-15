# lua 执行器

## 安装

`npm install @pomelo/lua --save`

## 接口

```ts
declare export class PomeloLua {
    constructor();
    doString(lua: string): { result: number; message: string };
}
```

## 示例
```ts
import { PomeloLua } from '@pomelo/lua';
const lua = new PomeloLua();
const {result, message} = lua.doString('result=0;message="success";');
lua.close(); //不用时需要关闭
```