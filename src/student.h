#pragma once
#include <fstream>
#include <iostream>
#include <memory>
class Person {
 public:
  virtual void Serialize(std::ofstream& ofs) const = 0;
  virtual void Show() const = 0;

 protected:
  // we cant delete object, only shared pointer ref count will
  virtual ~Person() = default;
  Person& operator=(const Person&) = default;
  std::string surname_;
  std::string address_;
};

inline int const MIN_STUDY_YEAR = 1;
inline int const MAX_STUDY_YEAR = 5;

class Student : public Person {
 public:
  Student(std::string surname, std::string address, std::string faculty,
          int study_year_);
  void Serialize(std::ofstream& ofs) const override;
  void Show() const override;
  std::string surname() const;
  std::string address() const;
  std::string faculty() const;
  int study_year() const;
  static std::shared_ptr<Person> CreateInstance(std::string surname,
                                                std::string address,
                                                std::string faculty,
                                                int study_year);

 private:
  std::string faculty_;
  int study_year_;
};

std::ostream& operator<<(std::ostream& os, const Student& s);
