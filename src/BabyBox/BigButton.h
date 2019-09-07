
enum BigButtonStatus {
  BUTTON_UP,
  BUTTON_UP_DOWN,
  BUTTON_DOWN,
  BUTTON_DOWN_UP,
  BUTTON_IDLE
};



class BigButton {

private:
  // up 930
  // middle 0
  // down 696
  static const int BUTTON_UP_LIMIT = 800;
  static const int BUTTON_DOWN_LIMIT = 300;
  static const int CHANGE_COUNT = 10;
  
  static const int STATE_UP = 0;
  static const int STATE_MIDDLE = 1;
  static const int STATE_DOWN = 2;

  int buttonPin;

  int lastReturnedStatus = STATE_UP;
  int lastStatus = STATE_UP;
  int changeCounter = 0;

  
public:

  BigButton(int pin) : buttonPin(pin) {
  }

  BigButtonStatus checkButton() {
    BigButtonStatus retState = BigButtonStatus::BUTTON_IDLE;
    
    int currentStatus = readCurrentButtonStatus();
    if (currentStatus != lastStatus) {
      lastStatus = currentStatus;
      changeCounter = 0;
    } else {
      if (changeCounter <= CHANGE_COUNT) changeCounter++;
    }
    
    if (changeCounter == CHANGE_COUNT && lastReturnedStatus != currentStatus) {
      if (currentStatus == STATE_UP) {
        retState = BigButtonStatus::BUTTON_UP;
      } else if (currentStatus == STATE_MIDDLE) {
        retState = lastReturnedStatus == STATE_UP ? BigButtonStatus::BUTTON_UP_DOWN : BigButtonStatus::BUTTON_DOWN_UP;
      } else if (currentStatus == STATE_DOWN) {
        retState = BigButtonStatus::BUTTON_DOWN;
      }
      lastReturnedStatus = currentStatus;
    }

    return retState;
  }


private:
  int readCurrentButtonStatus() {
    int val = analogRead(buttonPin);
    if (val > BUTTON_UP_LIMIT) {
      return STATE_UP;
    } else if (val < BUTTON_DOWN_LIMIT) {
      return STATE_MIDDLE;
    } else {
      return STATE_DOWN;
    }
  }

};
