declare export class PomeloLua {
    constructor();
    doString(lua: string): { result: number; message: string };
}
