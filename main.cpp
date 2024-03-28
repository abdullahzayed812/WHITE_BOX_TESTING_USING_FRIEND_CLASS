#include <iostream>

#include <assert.h>

#include <cctype>
#include <iostream>
#include <utility>
#include <vector>

class StudentGradesInfo {
 private:
  std::string studentId;
  std::vector<double> grades;
  std::vector<std::string> coursesNames;

  const double MAX_GRADE_PER_COURSE = 100.0;

  static int statisticsTotalPrints;
  friend class StudentGradesInfoWhiteBoxTesting;

  std::string toLowerCase(const std::string& str) const {
    std::string result;

    for (int i = 0; i < str.size(); i++) {
      result += tolower(str[i]);
    }

    return result;
  }

  double adjustGrade(double grade) const {
    if (grade < 0) {
      return 0;
    } else if (grade > this->MAX_GRADE_PER_COURSE) {
      return this->MAX_GRADE_PER_COURSE;
    }

    return grade;
  }

 public:
  StudentGradesInfo(std::string id) : studentId(id) {}

  bool addGrade(double grade, const std::string& courseName) {
    grade = this->adjustGrade(grade);

    for (int i = 0; i < (int)this->coursesNames.size(); i++) {
      if (this->toLowerCase(courseName) == this->toLowerCase(this->coursesNames[i])) {
        return false;
      }
    }

    this->coursesNames.push_back(courseName);
    this->grades.push_back(grade);

    return true;
  }

  void printAllCourses() const {
    StudentGradesInfo::statisticsTotalPrints++;

    std::cout << "Grades for student id: " << this->studentId << "\n";

    for (int i = 0; i < (int)this->coursesNames.size(); i++) {
      std::cout << "\t Course name: " << coursesNames[i] << "\t Grade: " << this->grades[i] << "\n";
    }
  }

  bool getCourseGradesInfo(int pos, std::pair<std::string, double>& gradesInfo) const {
    if (pos < 0 || pos >= (int)this->coursesNames.size()) {
      gradesInfo = std::make_pair("", -1);
      return false;
    }

    gradesInfo = std::make_pair(this->coursesNames[pos], this->grades[pos]);
    return true;
  }

  std::pair<double, double> getTotalGradesSum() const {
    double sum = 0, total = 0;

    for (int i = 0; i < (int)this->coursesNames.size(); i++) {
      sum += this->grades[i];
      total += this->MAX_GRADE_PER_COURSE;
    }

    return std::make_pair(sum, total);
  }

  std::string getStudentId() const { return this->studentId; }

  int getTotalCoursesCount() const { return this->coursesNames.size(); }
};

int StudentGradesInfo::statisticsTotalPrints = 0;

class StudentGradesInfoWhiteBoxTesting {
  private:
    const static int MAX_grade_PER_COURSE = 100.0;

  public:
    static void  testAdjustGrade() {
      std::cout << __func__ << "\n";

      StudentGradesInfo student("S001");

      assert(student.adjustGrade(50.1) == 50.1);
      assert(student.adjustGrade(-200) == 0);
      assert(student.adjustGrade(120) == 100);
      assert(student.adjustGrade(70) == 70);

      std::cout << "Adjust grade passed test.\n";
    }

    static void testAddGrade() {
      std::cout << __func__ << "\n";

      StudentGradesInfo student("S002");

      student.addGrade(80, "Math");

      assert(student.coursesNames.size() == student.grades.size() && student.coursesNames.size() == 1);

      student.addGrade(70, "Programming 1");

      assert(student.coursesNames.size() == student.grades.size() && student.coursesNames.size() == 2);

      student.addGrade(80, "Programming 1");
      
      assert(student.coursesNames.size() == student.grades.size() && student.coursesNames.size() == 2);

      assert(student.grades.back() == 70);
      assert(student.coursesNames.back() == "Programming 1");

      std::cout << "Add grade passed test.\n";
    }

    static void testStatisticsTotalPrint() {
      std::cout << __func__ << "\n";

      StudentGradesInfo student1("S001");
      StudentGradesInfo student2("S002");

      assert(StudentGradesInfo::statisticsTotalPrints == 0);
      
      student1.printAllCourses();

      assert(StudentGradesInfo::statisticsTotalPrints == 1);
      
      student1.addGrade(80, "Math");
      student1.printAllCourses();
      assert(StudentGradesInfo::statisticsTotalPrints == 2);
    
      student2.printAllCourses();   
      assert(StudentGradesInfo::statisticsTotalPrints == 3);

      std::cout << "Statistics total prints passed test.\n";
    }

    static void testAll() {
      StudentGradesInfoWhiteBoxTesting::testAdjustGrade();
      StudentGradesInfoWhiteBoxTesting::testAddGrade();
      StudentGradesInfoWhiteBoxTesting::testStatisticsTotalPrint();

      std::cout << "All test passed.\n";
    }

};

int main() {
  StudentGradesInfoWhiteBoxTesting::testAll(); 

  return 0;
}

