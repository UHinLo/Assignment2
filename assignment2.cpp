// Assignment 2
// Program to compute mean, standard deviation and standard error of a set of courses.
// Data is read from file
// U Hin Lo, 10916069, 21/02/2024

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<vector>
#include <numeric>
#include <algorithm>

// Check validity of the file path
bool check_file(const std::string& file_path)
{
  std::ifstream file(file_path);
  bool open = file.is_open();
  file.close();
  return open;
}
// Calculate mean
double calculate_mean(const std::vector<double>& data)
{
  double sum = 0.0;
  for(double value : data)
  {
    sum += value;
  }
  return sum / data.size();
}
// Calculate standard deviation
double calculate_standard_deviation(const std::vector<double>& data)
{
  double mean = calculate_mean(data);
  double sum = 0.0;
  for(double value : data)
  {
    sum += std::pow(value - mean, 2);
  }
  return std::sqrt(sum / (data.size() - 1));
}
// Calculate standard error in the mean
double calculate_standard_error(const std::vector<double>& data)
{
  double std = calculate_standard_deviation(data);
  return std / std::sqrt(data.size());
}

// Main function
int main()
{
  // Define variables
  char data_file[100];
  char repeat;
  float mark;
  int code;
  std::string choose;
  std::string display_order;
  std::string name;
  std::stringstream output;
  std::vector<std::string> data{};
  std::vector<double> course_marks{};
  std::vector<int> course_code{};
  std::vector<std::string> course_name{};
  std::vector<double> selected_marks{};
  // Ask user to enter filename
  std::cout<<"Enter data filename: ";
  while(!(std::cin>>data_file) || !check_file(data_file))
  {
    std::cout<<"File doesn't exist, Please enter a valid file name: ";
    std::cin.clear();
    std::cin.ignore(10000, '\n');
  }
  std::ifstream course_stream(data_file);
  std::string line;
  while(std::getline(course_stream, line))
  {
    // Read data and allocate them
    data.push_back(line);
    std::istringstream line_of_data(line);
    line_of_data>>mark;
    course_marks.push_back(mark);
    line_of_data>>code;
    course_code.push_back(code);
    name=line.substr(13);
    course_name.push_back(name);
  }
  // Close file
  course_stream.close();
  std::cout<<course_name.size()<<" courses data loaded successfully"<<std::endl;
  while(true)
  {
    // Ask User to choose
    std::cout<<"Enter the year interested (1/2/3/4) or 0 for all years or 5 for display order: ";
    while(!(std::cin>>choose) || !(choose >= "0") || !(choose <= "5") || choose.length() > 1)
    {
      std::cout<<"Please enter a valid input (0/1/2/3/4/5): ";
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
    std::cout<<"------------------------------------"<<std::endl;
    // All course
    if(choose[0] == '0')
    {
      std::vector<int>::iterator iterate_code = course_code.begin();
      std::vector<std::string>::iterator iterate_name = course_name.begin();
      std::vector<double>::iterator iterate_marks = course_marks.begin();
      for(; iterate_code != course_code.end() && iterate_name != course_name.end() && iterate_marks != course_marks.end(); ++iterate_code, ++iterate_marks, ++iterate_name)
      {
        output.clear();
        output.str("");
        output<<"PHYS "<<*iterate_code<<"   "<<*iterate_name<<" ";
        output<<std::fixed<<std::setprecision(1)<<*iterate_marks;
        std::cout<<output.str()<<std::endl;
      }
      //Print courses requested
      std::cout<<"------------------"<<std::endl;
      std::cout<<course_marks.size()<<" courses data selected"<<std::endl;
      std::cout<<"Mean: "<<std::fixed<<std::setprecision(1)<<calculate_mean(course_marks)<<std::endl;
      std::cout<<"Standard deviation: "<<std::fixed<<std::setprecision(1)<<calculate_standard_deviation(course_marks)<<std::endl;
      std::cout<<"Standard Error in Mean: "<<std::fixed<<std::setprecision(1)<<calculate_standard_error(course_marks)<<std::endl;
      std::cout<<"------------------------------------"<<std::endl;
    }
    // Determine display order
    else if(choose[0] == '5')
    {
      std::cout<<"Enter 'code' to display courses sorted by code or 'title' to display courses sorted by title"<<std::endl;
      while(!(std::cin>>display_order) || (display_order != "code" && display_order != "title"))
      {
        std::cout<<"Please enter a valid choose: "<<std::endl;
        std::cin.clear();
        std::cin.ignore(10000, '\n');
      }
      if(display_order == "code")
      {
        // Sort function based on code
        std::vector<size_t> indices(course_code.size());
        std::iota(indices.begin(), indices.end(), 0);
        // Sort the indices based on the values in course_code
        std::sort(indices.begin(), indices.end(), [&course_code](size_t i1, size_t i2)
        {
          return course_code[i1] < course_code[i2];
        });
        // Temporary vectors to hold the sorted values
        std::vector<int> new_code(course_code.size());
        std::vector<double> new_marks(course_marks.size());
        std::vector<std::string> new_name(course_name.size());
        // Reorder the vectors based on the sorted indices
        for(size_t i = 0; i < indices.size(); ++i)
        {
          new_code[i] = course_code[indices[i]];
          new_marks[i] = course_marks[indices[i]];
          new_name[i] = course_name[indices[i]];
        }
        // Renew vectors
        course_code.clear();
        course_code = new_code;
        course_marks.clear();
        course_marks = new_marks;
        course_name.clear();
        course_name = new_name;
        std::cout<<"Courses will now display in the order of course codes."<<std::endl;
      }
      else
      {
        // Sort function based on the title
        std::vector<size_t> indices(course_name.size());
        std::iota(indices.begin(), indices.end(), 0);
        // Sort the indices based on the first character in course_name
        std::sort(indices.begin(), indices.end(), [&course_name](size_t i1, size_t i2)
        {
          return course_name[i1][0] < course_name[i2][0];
        });
        // Temporary vectors to hold the sorted values
        std::vector<int> new_code(course_code.size());
        std::vector<double> new_marks(course_marks.size());
        std::vector<std::string> new_name(course_name.size());
        // Reorder the vectors based on the sorted indices
        for(size_t i = 0; i < indices.size(); ++i)
        {
          new_code[i] = course_code[indices[i]];
          new_marks[i] = course_marks[indices[i]];
          new_name[i] = course_name[indices[i]];
        }
        // Renew vectors
        course_code.clear();
        course_code = new_code;
        course_marks.clear();
        course_marks = new_marks;
        course_name.clear();
        course_name = new_name;
        std::cout << "Courses will now display in the order of the title of courses." << std::endl;
      }
    }
    // Specific year
    else
    {
      std::vector<int>::iterator iterate_code = course_code.begin();
      std::vector<std::string>::iterator iterate_name = course_name.begin();
      std::vector<double>::iterator iterate_marks = course_marks.begin();
      for(; iterate_code != course_code.end() && iterate_name != course_name.end() && iterate_marks != course_marks.end(); ++iterate_code, ++iterate_marks, ++iterate_name)
      {
        if(std::to_string(*iterate_code)[0] == choose[0])
        {
          // Print courses requested
          selected_marks.push_back(*iterate_marks);
          output.clear();
          output.str("");
          output<<"PHYS "<<*iterate_code<<"   "<<*iterate_name<<" ";
          output<<std::fixed<<std::setprecision(1)<<*iterate_marks;
          std::cout<<output.str()<<std::endl;
        }
      }
      std::cout<<"------------------"<<std::endl;
      std::cout<<selected_marks.size()<<" courses data selected"<<std::endl;
      std::cout<<"Mean: "<<std::fixed<<std::setprecision(1)<<calculate_mean(selected_marks)<<std::endl;
      std::cout<<"Standard deviation: "<<std::fixed<<std::setprecision(1)<<calculate_standard_deviation(selected_marks)<<std::endl;
      std::cout<<"Standard Error in Mean: "<<std::fixed<<std::setprecision(1)<<calculate_standard_error(selected_marks)<<std::endl;
      std::cout<<"------------------------------------"<<std::endl;
    }
    // Free memory
    selected_marks.clear();
    // Check if repeat or not
    std::cout<<"Do you want to check other years? (y/n): "<<std::endl;
    while(!(std::cin>>repeat) || (repeat != 'Y' && repeat != 'y' && repeat != 'N' && repeat != 'n'))
    {
      std::cout<<"Invalid input. Please enter either 'y' or 'n': "<<std::endl;
      std::cin.clear();
      std::cin.ignore(10000, '\n');
    }
    if(repeat == 'n' || repeat == 'N')
      break;
  }
  std::cout<<"---End of program---"<<std::endl;
  return 0;
}
