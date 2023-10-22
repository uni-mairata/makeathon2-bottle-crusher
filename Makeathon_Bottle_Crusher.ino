/**
  * Most code taken from stepper motor video tutorial lesson.
  * https://www.youtube.com/watch?v=TQ7R2bY-MWU 
  * by Robojax
  * Modified and other parts written by Maika Hirata.
  */

// pin constants
const int pin1 = 10; // IN1
const int pin2 = 11; // IN2
const int pin3 = 12; // IN3
const int pin4 = 13; // IN4
const int button = 3;

// pole positions
int pole1[] = {0, 0, 0, 0,  0, 1, 1, 1,  0};
int pole2[] = {0, 0, 0, 1,  1, 1, 0, 0,  0};
int pole3[] = {0, 1, 1, 1,  0, 0, 0, 0,  0};
int pole4[] = {1, 1, 0, 0,  0, 0, 0, 1,  0};

int poleStep = 0;
int directionStatus = 3; // stores direction status (1 = CCW, 2 = CW, 3 = stop)

void setup() {
  pinMode(pin1, OUTPUT);
  pinMode(pin2, OUTPUT);
  pinMode(pin3, OUTPUT);
  pinMode(pin4, OUTPUT);

  pinMode(button, INPUT_PULLUP); // HIGH = not pressed, LOW = pressed
  
  Serial.begin(9600);
}

void loop() {
  if (digitalRead(button) == LOW) {
    pullPulley(5000, 0);
    delay(550); // pause 0.55 seconds
    pullPulley(5000, 1);
  } // if
}

/**
  * Moves stepper motor in specified direction.
  * @param c integer representing the pol of motor
  *
  * www.Robojax.com code June 2019
  */
void driveStepper(int c) {
  digitalWrite(pin1, pole1[c]);
  digitalWrite(pin2, pole2[c]);
  digitalWrite(pin3, pole3[c]);
  digitalWrite(pin4, pole4[c]);
} // drivestepper

/**
  * Pull pulley up or down for a certain duration.
  * @param duration number of milliseconds to move the stepper motor
  * @param direction 0 = move the pulley down, 1 = move the pulley up
  */
void pullPulley(int duration, int direction) {
  // TODO: CHANGE UP AND DOWN VALUE DEPENDING ON THE ORIENTATION OF THE MOTOR
  for (int i = 0; i < duration; i++) {
    if (direction == 0) {
      poleStep--;
    } else if (direction == 1) {
      poleStep++;
    } else {
      return;
    } // if
    driveStepper(poleStep);
    keepPoleStepInRange();
    delay(1); // necessary so motor has enough time to move from one step to next step
  } // for

  driveStepper(8); // stop the motor
} // pullPulleyUp

void keepPoleStepInRange() {
  if (poleStep > 7) {
    poleStep = 0;
  } // if

  if (poleStep < 0) {
    poleStep = 7;
  } // if
} // keepInRange
