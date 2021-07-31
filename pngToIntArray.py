from PIL import Image

img = Image.open("Frame.png")
img = img.convert("RGBA")
datas = img.getdata()

output = []
for item in datas:
    if (item[0] == 255):
        output.append(1)
    else:
        output.append(0)

print(output)
f = open("frame.txt", "w")
for element in output:

    f.write(str(element) + ",")
f.close()

print(len(output))
