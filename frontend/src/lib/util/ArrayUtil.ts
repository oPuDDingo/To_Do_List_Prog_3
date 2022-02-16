

export class ArrayUtil {
    static cutElement(array: any[], element: any) : void {
        let i = array.indexOf(element);
        if(i != -1) {
            array.splice(i, 1);
        }
    }
}