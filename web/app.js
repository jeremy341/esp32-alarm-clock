let port;
let writer;

const canvas = document.getElementById("c");
const ctx = canvas.getContext("2d");

// simple test pattern
for (let x = 0; x < 32; x++) {
    for (let y = 0; y < 32; y++) {
        ctx.fillStyle = (x + y) % 2 === 0 ? "red" : "blue";
        ctx.fillRect(x, y, 1, 1);
    }
}

async function connect() {
    port = await navigator.serial.requestPort();
    await port.open({ baudRate: 115200 });
    writer = port.writable.getWriter();
    alert("Connected!");
}

function toRGB565(r, g, b) {
    return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3);
}

async function send() {
    const img = ctx.getImageData(0, 0, 32, 32).data;

    let packet = [];

    // header
    packet.push(0xAA, 0x55);
    packet.push(32); // width
    packet.push(32); // height

    for (let i = 0; i < img.length; i += 4) {
        let r = img[i];
        let g = img[i+1];
        let b = img[i+2];

        let color = toRGB565(r, g, b);

        packet.push((color >> 8) & 0xFF);
        packet.push(color & 0xFF);
    }

    await writer.write(new Uint8Array(packet));
}