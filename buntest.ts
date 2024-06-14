import {  dlopen, FFIType, suffix, ptr } from "bun:ffi";
const { cstring, int, pointer } = FFIType;
function encodeCString(str:string){
    const enc = new TextEncoder()
    const encoded = enc.encode(str) 
    return ptr(encoded)
}
let lib = dlopen("lib.dll",{
    hello:{
        args:[cstring],
        returns:FFIType.void
    },
    matrix_multiply:{
        args:[pointer,pointer, pointer, int],
        returns:pointer
    },
    matrix_add:{
        args:[pointer,pointer, pointer, int],
        returns:pointer 
    },
    memc:{
        args:[],
        returns:pointer
    },
    freemem:{
        args:[pointer],
        returns:FFIType.void
    },
    genRandomImage:{
        args:[int, int, pointer],
        returns:FFIType.void
    },
    insert_node:{
        args:[pointer, int],
        returns:FFIType.void
    },
    delete_node:{
        args:[pointer, int],
        returns:FFIType.void
    },
    print_list:{
     args:[pointer],
     returns:FFIType.void
    }
});
const N = 3;
const A = new Int32Array([5, 2, 3, 4, 5]);
const B = new Int32Array([6, 7, 8, 9, 10]);
const C = new Int32Array(N);
const name = process.argv[2] ?? "Ayo";
const enc = new TextEncoder()
const encoded = enc.encode(name)
// Create initial head pointer (null)
const headBuffer = new ArrayBuffer(8); // Pointer size (64-bit)
const headView = new DataView(headBuffer);
headView.setBigUint64(0, 0n, true); // Set head to null (0)

// Get pointer to head
const headPtr = ptr(new Uint8Array(headBuffer));
lib.symbols.insert_node(headPtr, 8)
lib.symbols.print_list(headPtr)
lib.symbols.hello(encodeCString(name))
console.log(lib.symbols.matrix_multiply(A, B, C, N), lib.symbols.matrix_add(A,B,C,N) )
lib.symbols.genRandomImage(400, 400, encodeCString(name))