#include "student.h"

Student::Student(std::string surname, std::string address, std::string faculty,
                 int study_year) {
  surname_ = surname;
  address_ = address;
  faculty_ = faculty;
  study_year_ = study_year;
}

void Student::Serialize(std::ofstream& ofs) const {
  ofs << surname_ << std::endl
    << address_ << std::endl
    << faculty_ << std::endl
    << study_year_ << std::endl
    << std::endl;
}

void Student::Show() const { std::cout << *this; }

std::string Student::surname() const { return surname_; }

std::string Student::address() const { return address_; }

std::string Student::faculty() const { return faculty_; }

int Student::study_year() const { return study_year_; }

std::shared_ptr<Person> Student::CreateInstance(std::string surname,
                                                std::string address,
                                                std::string faculty,
                                                int study_year) {
  if(study_year < MIN_STUDY_YEAR || study_year > MAX_STUDY_YEAR)
  {
    throw std::invalid_argument("incorrect year value");
  }
  return std::make_shared<Student>(surname, address, faculty, study_year);
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
  os << "Информация о студенте:" << std::endl;
  os << " - Фамилия: " << s.surname() << std::endl;
  os << " - Адрес: " << s.address() << std::endl;
  os << " - Факультет: " << s.faculty() << std::endl;
  os << " - Курс: " << s.study_year() << std::endl << std::endl;
  return os;
}
