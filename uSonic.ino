#include <Servo.h>
Servo myServo;
int left= 180;
int right = 15;
int mid = 90;

int lDiag = 135;
int rDiag = 37;

//ultrasonic init
int echo = A4;
int trig = A5;

int lDist = 0,lDiagDist = 0, rDist = 0,rDiagDist = 0, mDist = 0;

//Right wheel variable init
int spdR = 5;
int fR = 6;
int bR = 7;
//Left wheel variable init
int spdL = 11;
int fL = 9;
int bL = 8;

//wheel speed
int SPD = 500;

int servoDelay = 250;
int mDelay = 400;
int mDiagDelay = 225;
int dist = 60;

void backward()
{
    analogWrite(spdR, SPD);
    analogWrite(spdL, SPD); 
    digitalWrite(fR,LOW);
    digitalWrite(bR,HIGH);
    digitalWrite(fL, LOW);
    digitalWrite(bL, HIGH);
}

void forward()
{
    analogWrite(spdR, SPD);
    analogWrite(spdL, SPD); 
    digitalWrite(fR, HIGH);
    digitalWrite(bR, LOW);
    digitalWrite(fL, HIGH);
    digitalWrite(bL, LOW);
}

void mLeft()
{
    analogWrite(spdL, SPD);
    analogWrite(spdR, SPD);
    digitalWrite(fL, HIGH);
    digitalWrite(bL, LOW);
    digitalWrite(fR, LOW);
    digitalWrite(bR, HIGH);
}

void mRight()
{
    analogWrite(spdR, SPD);
    analogWrite(spdL, SPD);
    digitalWrite(fR, HIGH);
    digitalWrite(bR, LOW);
    digitalWrite(fL, LOW);
    digitalWrite(bL, HIGH);
}

void stop()
{
    digitalWrite(spdR, LOW);
    digitalWrite(spdL, LOW);
}

int Distance()
{
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(dist);
    digitalWrite(trig, LOW);
    float cmDist = pulseIn(echo, HIGH);
    cmDist = cmDist/58;
    return (int)cmDist;
}

void setup()
{
    Serial.begin(9600);
    myServo.attach(3);

    pinMode(echo, INPUT);
    pinMode(trig, OUTPUT);

    pinMode(spdR,OUTPUT);
    pinMode(fR,OUTPUT);
    pinMode(bR,OUTPUT);

    pinMode(spdL, OUTPUT);
    pinMode(fL,OUTPUT);
    pinMode(bL,OUTPUT);
    stop();

    myServo.write(mid);
    delay(servoDelay);
    mDist = Distance(); 
}

void panLR()
{
    if(rDist > lDist) {
        mLeft();
        delay(mDelay);
    }
    else if(lDist > rDist) {
        mRight();
        delay(mDelay);
    }
    stop();
}

void panLRDiag()
{
    if((rDiagDist <= dist) || (lDiagDist <= dist)) {
        if(rDiagDist > lDiagDist) {
            mLeft();
            delay(mDiagDelay);
            stop();
        }
        else if(lDiagDist > rDiagDist) {
            mRight();
            delay(mDiagDelay);
            stop();
        }
    }
}

void panFwd()
{
    Serial.println("No Obstacle");

    myServo.write(lDiag);
    delay(servoDelay);
    lDiagDist = Distance();
    Serial.print("lDiagDist = ");
    Serial.println(lDiagDist);

    myServo.write(rDiag);
    delay(servoDelay);
    rDiagDist = Distance();
    Serial.print("rDiagDist = ");
    Serial.println(rDiagDist);

    myServo.write(mid);
    delay(servoDelay);
    mDist = Distance();
    Serial.print("mDist = ");
    Serial.println(mDist);

    panLRDiag();
}
void loop()
{
    while(mDist <= dist)
    {
        stop();         
        myServo.write(left);
        delay(servoDelay);
        lDist = Distance();
        Serial.print("lDist = ");
        Serial.println(lDist);

        myServo.write(right);
        delay(servoDelay);
        rDist = Distance();
        Serial.print("rDist = ");
        Serial.println(rDist);
        panLR();

        myServo.write(mid);
        delay(servoDelay);
        mDist = Distance();
        Serial.print("mDist = ");
        Serial.println(mDist);
    }
        forward();
        panFwd();
}
