/*#include <NMEAGPS.h>
#include <GPSport.h>
#include <Streamers.h>

NMEAGPS  gps;

//------------------------------------------------------------
//  Define a set of GPS fix information.  It will
//  hold on to the various pieces as they are received from
//  an RMC sentence.  It can be used anywhere in your sketch.

static gps_fix  fix;

//----------------------------------------------------------------
//  This function gets called about once per second, during the GPS
//  quiet time.  It's the best place to do anything that might take
//  a while: print a bunch of things, write to SD, send an SMS, etc.
//
//  By doing the "hard" work during the quiet time, the CPU can get back to
//  reading the GPS chars as they come in, so that no chars are lost.

static void doSomeWork()
{
	// Print all the things!

	trace_all(DEBUG_PORT, gps, fix);

} // doSomeWork

  //------------------------------------
  //  This is the main GPS parsing loop.

void GPSloop()
{
	while (gps.available(gpsPort)) {
		fix = gps.read();
	}

} // GPSloop

  //--------------------------

void setup()
{
	DEBUG_PORT.begin(115200);
	while (!DEBUG_PORT);

	DEBUG_PORT.print(F("NMEA.INO: started\n"));
	DEBUG_PORT.print(F("  fix object size = "));
	DEBUG_PORT.println(sizeof(gps.fix()));
	DEBUG_PORT.print(F("  gps object size = "));
	DEBUG_PORT.println(sizeof(gps));
	DEBUG_PORT.println(F("Looking for GPS device on " GPS_PORT_NAME));


	if (gps.merging == NMEAGPS::NO_MERGING) {
		DEBUG_PORT.print(F("\nWARNING: displaying data from "));
		DEBUG_PORT.print(gps.string_for(LAST_SENTENCE_IN_INTERVAL));
		DEBUG_PORT.print(F(" sentences ONLY, and only if "));
		DEBUG_PORT.print(gps.string_for(LAST_SENTENCE_IN_INTERVAL));
		DEBUG_PORT.println(F(" is enabled.\n"
			"  Other sentences may be parsed, but their data will not be displayed."));
	}

	DEBUG_PORT.print(F("\nGPS quiet time is assumed to begin after a "));
	DEBUG_PORT.print(gps.string_for(LAST_SENTENCE_IN_INTERVAL));
	DEBUG_PORT.println(F(" sentence is received.\n"
		"  You should confirm this with NMEAorder.ino\n"));

	trace_header(DEBUG_PORT);
	DEBUG_PORT.flush();

	gpsPort.begin(9600);
}

//--------------------------

void loop()
{
	GPSloop();
}

*/
/*

#include <MPU6050/MPU6050.h>

#include <SysCall.h>
#include <sdios.h>
#include <SdFatConfig.h>
#include <SdFat.h>
#include <MinimumSerial.h>
#include <FreeStack.h>
#include <BlockDriver.h>
#include "SparkFunMPL3115A2.h"

 MPL3115A2 Barometric Pressure Sensor Library Example Code
 By: Nathan Seidle
 SparkFun Electronics
 Date: September 24th, 2013
 License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

 Uses the MPL3115A2 library to display the current altitude and temperature

 Hardware Connections (Breakoutboard to Arduino):
 -VCC = 3.3V
 -SDA = A4 (use inline 10k resistor if your board is 5V)
 -SCL = A5 (use inline 10k resistor if your board is 5V)
 -INT pins can be left unconnected for this demo

 During testing, GPS with 9 satellites reported 5393ft, sensor reported 5360ft (delta of 33ft). Very close!
 During testing, GPS with 8 satellites reported 1031ft, sensor reported 1021ft (delta of 10ft).

 Available functions:
 .begin() Gets sensor on the I2C bus.
 .readAltitude() Returns float with meters above sealevel. Ex: 1638.94
 .readAltitudeFt() Returns float with feet above sealevel. Ex: 5376.68
 .readPressure() Returns float with barometric pressure in Pa. Ex: 83351.25
 .readTemp() Returns float with current temperature in Celsius. Ex: 23.37
 .readTempF() Returns float with current temperature in Fahrenheit. Ex: 73.96
 .setModeBarometer() Puts the sensor into Pascal measurement mode.
 .setModeAltimeter() Puts the sensor into altimetery mode.
 .setModeStandy() Puts the sensor into Standby mode. Required when changing CTRL1 register.
 .setModeActive() Start taking measurements!
 .setOversampleRate(byte) Sets the # of samples from 1 to 128. See datasheet.
 .enableEventFlags() Sets the fundamental event flags. Required during setup.

 */
/*
#include <Wire.h>
#include "SparkFunMPL3115A2.h"

 //Create an instance of the object
MPL3115A2 myPressure;

void setup()
{
	Serial.begin(115200);  // Start serial for output
	Serial.println("Start");
	Wire.begin();        // Join i2c bus

	myPressure.begin(); // Get sensor online

	//Configure the sensor
	myPressure.setModeAltimeter(); // Measure altitude above sea level in meters
	//myPressure.setModeBarometer(); // Measure pressure in Pascals from 20 to 110 kPa

	myPressure.setOversampleRate(4); // Set Oversample to the recommended 128
	myPressure.enableEventFlags(); // Enable all three pressure and temp event flags 
	Serial.println("Test");
}

void loop()
{
	//float altitude = myPressure.readAltitude();
	//Serial.print("Altitude(m):");
	//Serial.print(altitude, 2);

	float altitude = myPressure.readAltitudeFt();
	Serial.print(" Altitude(ft):");
	Serial.print(altitude, 2);

	//float pressure = myPressure.readPressure();
	//Serial.print("Pressure(Pa):");
	//Serial.print(pressure, 2);

	//float temperature = myPressure.readTemp();
	//Serial.print(" Temp(c):");
	//Serial.print(temperature, 2);

	float temperature = myPressure.readTempF();
	Serial.print(" Temp(f):");
	Serial.print(temperature, 2);

	Serial.println();
}


/*
#include <Wire.h>

void setup() {
	Serial.begin(115200); //*****  make sure serial monitor baud matches *****

	// Leonardo: wait for serial port to connect
	while (!Serial)
	{
	}

	
}  // end of setup

void loop() {
	Serial.println();
	Serial.println("I2C scanner. Scanning ...");
	byte count = 0;

	Wire.begin();
	for (byte i = 1; i < 120; i++)
	{
		Wire.beginTransmission(i);
		if (Wire.endTransmission() == 0)
		{
			Serial.print("Found address: ");
			Serial.print(i, DEC);
			Serial.print(" (0x");
			Serial.print(i, HEX);
			Serial.println(")");
			count++;
			delay(1);  // maybe unneeded?
		} // end of good response
	} // end of for loop
	Serial.println("Done.");
	Serial.print("Found ");
	Serial.print(count, DEC);
	Serial.println(" device(s).");
	delay(1000);
}*/
/*
const int basePin = 42, pinLength = 5;

void setup() {
	for (int i = basePin; i < pinLength; i++) {
		pinMode(i, OUTPUT);
	}
	Serial.begin(115200);
	Serial.println("INIT!");
}

void loop() {
	for (int i = basePin; i < basePin + pinLength; i++) {
		if (i == basePin) {
			digitalWrite(basePin + pinLength - 1, LOW);
		} else {
			digitalWrite(i - 1, LOW);
		}
		digitalWrite(i, HIGH);
		Serial.println(i);
		digitalWrite(LED_BUILTIN, HIGH);
		delay(500);
		digitalWrite(LED_BUILTIN, LOW);
		delay(500);
	}
}
*/

/*
void setup() {
	Serial.begin(115200);
	Serial2.begin(115200);
	Serial.println("Init.");
}

void loop() {
	//Serial2.println("Test!");
	while (Serial2.available()) {
		Serial.print((char) Serial2.read());
	}
}
*/
// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project

/*
#include "I2Cdev.h"

#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file

// Arduino Wire library is required if I2Cdev I2CDEV_ARDUINO_WIRE implementation
// is used in I2Cdev.h
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
#include "Wire.h"
#endif

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high


  // uncomment "OUTPUT_READABLE_QUATERNION" if you want to see the actual
  // quaternion components in a [w, x, y, z] format (not best for parsing
  // on a remote host such as Processing or something though)
  //#define OUTPUT_READABLE_QUATERNION

  // uncomment "OUTPUT_READABLE_EULER" if you want to see Euler angles
  // (in degrees) calculated from the quaternions coming from the FIFO.
  // Note that Euler angles suffer from gimbal lock (for more info, see
  // http://en.wikipedia.org/wiki/Gimbal_lock)
  //#define OUTPUT_READABLE_EULER

  // uncomment "OUTPUT_READABLE_YAWPITCHROLL" if you want to see the yaw/
  // pitch/roll angles (in degrees) calculated from the quaternions coming
  // from the FIFO. Note this also requires gravity vector calculations.
  // Also note that yaw/pitch/roll angles suffer from gimbal lock (for
  // more info, see: http://en.wikipedia.org/wiki/Gimbal_lock)
//#define OUTPUT_READABLE_YAWPITCHROLL

// uncomment "OUTPUT_READABLE_REALACCEL" if you want to see acceleration
// components with gravity removed. This acceleration reference frame is
// not compensated for orientation, so +X is always +X according to the
// sensor, just without the effects of gravity. If you want acceleration
// compensated for orientation, us OUTPUT_READABLE_WORLDACCEL instead.
//#define OUTPUT_READABLE_REALACCEL

//uncomment "OUTPUT_READABLE_WORLDACCEL" if you want to see acceleration
// components with gravity removed and adjusted for the world frame of
// reference (yaw is relative to initial orientation, since no magnetometer
// is present in this case). Could be quite handy in some cases.
#define OUTPUT_READABLE_WORLDACCEL

// uncomment "OUTPUT_TEAPOT" if you want output that matches the
// format used for the InvenSense teapot demo
//#define OUTPUT_TEAPOT



#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards
#define LED_PIN 13 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float euler[3];         // [psi, theta, phi]    Euler angle container
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// packet structure for InvenSense teapot demo
uint8_t teapotPacket[14] = { '$', 0x02, 0,0, 0,0, 0,0, 0,0, 0x00, 0x00, '\r', '\n' };

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
	// join I2C bus (I2Cdev library doesn't do this automatically)
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
	Wire.begin();
	Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
	Fastwire::setup(400, true);
#endif

	// initialize serial communication
	// (115200 chosen because it is required for Teapot Demo output, but it's
	// really up to you depending on your project)
	Serial.begin(115200);

	// NOTE: 8MHz or slower host processors, like the Teensy @ 3.3V or Arduino
	// Pro Mini running at 3.3V, cannot handle this baud rate reliably due to
	// the baud timing being too misaligned with processor ticks. You must use
	// 38400 or slower in these cases, or use some kind of external separate
	// crystal solution for the UART timer.

	// initialize device
	Serial.println(F("Initializing I2C devices..."));
	mpu.initialize();

	// verify connection
	Serial.println(F("Testing device connections..."));
	Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

	// load and configure the DMP
	Serial.println(F("Initializing DMP..."));
	devStatus = mpu.dmpInitialize();

	// supply your own gyro offsets here, scaled for min sensitivity
	mpu.setXGyroOffset(220);
	mpu.setYGyroOffset(76);
	mpu.setZGyroOffset(-85);
	mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

	// make sure it worked (returns 0 if so)
	if (devStatus == 0) {
		// turn on the DMP, now that it's ready
		Serial.println(F("Enabling DMP..."));
		mpu.setDMPEnabled(true);

		// get expected DMP packet size for later comparison
		packetSize = mpu.dmpGetFIFOPacketSize();
		dmpReady = true;
	} else {
		// ERROR!
		// 1 = initial memory load failed
		// 2 = DMP configuration updates failed
		// (if it's going to break, usually the code will be 1)
		Serial.print(F("DMP Initialization failed (code "));
		Serial.print(devStatus);
		Serial.println(F(")"));
	}

	// configure LED for output
	pinMode(LED_PIN, OUTPUT);
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================

void loop() {
	// if programming failed, don't try to do anything
	if (!dmpReady) return;

	// wait for MPU interrupt or extra packet(s) available
	uint32_t start = millis();
	while (fifoCount < packetSize) {
		fifoCount = mpu.getFIFOCount();
	}
	uint32_t delta = millis() - start;

	// get current FIFO count
	fifoCount = mpu.getFIFOCount();

	// check for overflow (this should never happen unless our code is too inefficient)
	if (fifoCount >= 1024) {
		// reset so we can continue cleanly
		mpu.resetFIFO();
		fifoCount = mpu.getFIFOCount();
		Serial.println(F("FIFO overflow!"));
	} else {
		// read a packet from FIFO
		mpu.getFIFOBytes(fifoBuffer, packetSize);

		// track FIFO count here in case there is > 1 packet available
		// (this lets us immediately read more without waiting for an interrupt)
		fifoCount -= packetSize;
#ifdef OUTPUT_READABLE_QUATERNION
		// display quaternion values in easy matrix form: w x y z
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		Serial.print("quat\t");
		Serial.print(q.w);
		Serial.print("\t");
		Serial.print(q.x);
		Serial.print("\t");
		Serial.print(q.y);
		Serial.print("\t");
		Serial.println(q.z);
#endif

#ifdef OUTPUT_READABLE_EULER
		// display Euler angles in degrees
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetEuler(euler, &q);
		Serial.print("euler\t");
		Serial.print(euler[0] * 180 / M_PI);
		Serial.print("\t");
		Serial.print(euler[1] * 180 / M_PI);
		Serial.print("\t");
		Serial.println(euler[2] * 180 / M_PI);
#endif

#ifdef OUTPUT_READABLE_YAWPITCHROLL
		// display Euler angles in degrees
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
		Serial.print("ypr\t");
		Serial.print(ypr[0] * 180 / M_PI);
		Serial.print("\t");
		Serial.print(ypr[1] * 180 / M_PI);
		Serial.print("\t");
		Serial.println(ypr[2] * 180 / M_PI);
#endif

#ifdef OUTPUT_READABLE_REALACCEL
		// display real acceleration, adjusted to remove gravity
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetAccel(&aa, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
		Serial.print("areal\t");
		Serial.print(aaReal.x);
		Serial.print("\t");
		Serial.print(aaReal.y);
		Serial.print("\t");
		Serial.println(aaReal.z);
#endif

#ifdef OUTPUT_READABLE_WORLDACCEL
		// display initial world-frame acceleration, adjusted to remove gravity
		// and rotated based on known orientation from quaternion
		mpu.dmpGetQuaternion(&q, fifoBuffer);
		mpu.dmpGetAccel(&aa, fifoBuffer);
		mpu.dmpGetGravity(&gravity, &q);
		mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
		mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
		Serial.print("aworld\t");
		Serial.print(aaWorld.x);
		Serial.print("\t");
		Serial.print(aaWorld.y);
		Serial.print("\t");
		Serial.println(aaWorld.z);
#endif

#ifdef OUTPUT_TEAPOT
		// display quaternion values in InvenSense Teapot demo format:
		teapotPacket[2] = fifoBuffer[0];
		teapotPacket[3] = fifoBuffer[1];
		teapotPacket[4] = fifoBuffer[4];
		teapotPacket[5] = fifoBuffer[5];
		teapotPacket[6] = fifoBuffer[8];
		teapotPacket[7] = fifoBuffer[9];
		teapotPacket[8] = fifoBuffer[12];
		teapotPacket[9] = fifoBuffer[13];
		Serial.write(teapotPacket, 14);
		teapotPacket[11]++; // packetCount, loops at 0xFF on purpose
#endif
		blinkState = !blinkState;
		digitalWrite(LED_PIN, blinkState);
	}
}
*/