var fs = require("fs");
var SerialPort = require('serialport');
var Buffer = require('buffer').Buffer;
const rimraf = require('rimraf');

var readline = require('readline');

var rl = readline.createInterface({
	input: process.stdin,
	output: process.stdout
});

var payloadBuffer = Buffer.alloc(50 * 1024);//50KB
var payloadIndex = 0;
var stream = fs.createWriteStream("./Camera Test.dat");
var bytes = 0;
var packetCount = 0;

try {
	fs.mkdirSync("./images/");
} catch(error) {
	//console.error("Failed to create packets directory! " + error);
}
rimraf('./images/*', function () {  });

var openSerialFunc;
var lastByte = -1;
function openSerialFunction() {
	console.log("trying to open serial port");
	serialPort = new SerialPort("COM6", {
		baudRate: 115200
	});
	serialPort.on('error', (err) => console.log("Serial port error: " + err) );
	serialPort.on('open', () => {
		console.log("Serial port is now open!");
		clearInterval(openSerialFunc);
	});

	serialPort.on("close", () => {
		console.log("Serial port closed");
		stream.end();
		clearInterval(second);
		setTimeout(() => process.exit(), 1000);
	});

	serialPort.on('data', function (data) {
		stream.write(data);
		bytes += data.length;
		for(var i = 0; i < data.length; i++) {//Process each byte
			var byte = data.readUInt8(i);
			handleByte(lastByte, byte);
			lastByte = byte;
		}
	});
}


var image = new Uint8Array(1000000);
var imageIndex = 0;

var inFrame = false;
function handleByte(last, byte) {
	if(!inFrame) {
		if(last == 0xFF && byte == 0xD8) {// start of new frame
			image[imageIndex++] = last;
			inFrame = true;
		}
	}

	if(inFrame) {
		image[imageIndex++] = byte;
		if(last == 0xFF && byte == 0xD9) {
			console.log("Saving image - " + imageIndex + " bytes");
			var toSend = new Uint8Array(imageIndex);
			for(var i = 0; i < imageIndex; i++) {
				toSend[i] = image[i];
			}
			fs.writeFile("./images/img" + (packetCount++) + ".jpg", toSend, function(err) {
				if(err) {
					console.error("Failed to write packet file! " + err);
				}
			});
			imageIndex = 0;
			inFrame = false;
		}
	} else {//Normal print message
		process.stdout.write(String.fromCharCode(byte));
	}
}

var second = setInterval(() => {
	//console.log(bytes);
	bytes = 0;
}, 1000);

openSerialFunc = setInterval(openSerialFunction, 100);

rl.question("", function(answer) {
	serialPort.close();
});
