
from PIL import Image
import sys

def export_2bpp(path,out_path):
    img=Image.open(path).convert("L")
    w,h=img.size
    data=bytearray()
    for y in range(h):
        for x in range(0,w,4):
            byte=0
            for i in range(4):
                px=img.getpixel((x+i,y))
                val=px//64
                byte|=(val&0x03)<<(6-2*i)
            data.append(byte)
    with open(out_path,"wb") as f:
        f.write(data)

if __name__=="__main__":
    export_2bpp(sys.argv[1],sys.argv[2])
