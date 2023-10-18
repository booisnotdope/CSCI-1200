// File:     date.h
// Purpose:  Header file with declaration of the Date class, including
//   member functions and private member variables.

class Time {
public:
  Time();
  Time(int hours, int mins, int secs);

  // ACCESSORS
  int getSecond() const;
  int getMinute() const;
  int getHour() const;

  // MODIFIERS
  void setSecond(int secs);
  void setMinute(int mins);
  void setHour(int hours);
  void increment();

  // other member functions that operate on date objects

  void PrintAMPM();

private:  // REPRESENTATION (member variables)
  int secs;
  int mins;
  int hours;
};
bool IsEarlierThan(const Time& t1, const Time& t2);

