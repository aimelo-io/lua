# lua 执行器

## 环境要求

`npm install cmake-js -g`
`cmake`

## 安装

`npm install @aimelo/lua --save`

## 接口

```ts
declare export class AimeloLua {
    constructor();
    doString(lua: string): { result: number; message: string };
}
```

## 示例
```ts
import { AimeloLua } from '@aimelo/lua';
const lua = new AimeloLua();
const {result, message} = lua.doString('result=0;message="success";');
lua.close(); //不用时需要关闭
```