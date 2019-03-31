#ifndef BPRINTER_TABLE_PRINTER_H_
#define BPRINTER_TABLE_PRINTER_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

namespace bprinter {
class endl{};
class TablePrinter{
public:
  TablePrinter(std::ostream * output, const std::string & separator = "|");
  ~TablePrinter();

  int get_num_columns() const;
  int get_table_width() const;
  void set_separator(const std::string & separator);


  void AddColumn(const std::string & header_name, int column_width);
  void PrintHeader();
  void PrintFooter();

  TablePrinter& operator<<(endl input){
    while (current_column_index_ != 0){
      *this << "";
    }
    return *this;
  }

  // Can we merge these?
  TablePrinter& operator<<(float input);
  TablePrinter& operator<<(double input);

    template<typename T> TablePrinter& operator<<(T input){
    if (current_column_index_ == 0)
      *out_stream_ << "|";

    if(alignment_ == LEFT) {
        *out_stream_ << std::left;
    }
    else if (alignment_ == RIGHT) {
        *out_stream_ << std::right;
    }

    const int column_width = column_widths_.at(current_column_index_);
    *out_stream_ << std::setw(column_width);
    if (alignment_ == CENTER) {
        *out_stream_ << padString(SSTR(input), column_width);
    } else {
        *out_stream_ << input;
    }


    if (current_column_index_ == get_num_columns()-1){
      *out_stream_ << "|\n";
      current_row_index_ = current_row_index_ + 1;
      current_column_index_ = 0;
    } else {
      *out_stream_ << separator_;
      current_column_index_ = current_column_index_ + 1;
    }

    return *this;
  }




private:

    enum Alignment {
        LEFT = 0,
        RIGHT,
        CENTER
    };

  std::string padString(const std::string & str, int width) {
      if (width <= str.length()) {
          return str;
      }
      int white_spaces = width - str.length();
      int left_padding = (white_spaces + 1) / 2;
      int right_padding = white_spaces - left_padding;
      return std::string(left_padding, ' ') + str + std::string(right_padding, ' ');
  }

  void PrintHorizontalLine();

    template<typename T> void OutputDecimalNumber(T input){
        // If we cannot handle this number, indicate so
        if (input < 10*(column_widths_.at(current_column_index_)-1) || input > 10*column_widths_.at(current_column_index_)){
            std::stringstream string_out;
            string_out << std::setiosflags(std::ios::fixed)
                       << std::setprecision(column_widths_.at(current_column_index_))
                       << std::setw(column_widths_.at(current_column_index_))
                       << input;

            std::string string_rep_of_number = string_out.str();

            string_rep_of_number[column_widths_.at(current_column_index_)-1] = '*';
            std::string string_to_print = string_rep_of_number.substr(0, column_widths_.at(current_column_index_));
            *out_stream_ << string_to_print;
        } else {

            // determine what precision we need
            int precision = column_widths_.at(current_column_index_) - 1; // leave room for the decimal point
            if (input < 0)
                --precision; // leave room for the minus sign

            // leave room for digits before the decimal?
            if (input < -1 || input > 1){
                int num_digits_before_decimal = 1 + (int)log10(std::abs(input));
                precision -= num_digits_before_decimal;
            }
            else
                precision --; // e.g. 0.12345 or -0.1234

            if (precision < 0)
                precision = 0; // don't go negative with precision

            *out_stream_ << std::setiosflags(std::ios::fixed)
                         << std::setprecision(precision)
                         << std::setw(column_widths_.at(current_column_index_))
                         << input;
        }

        if (current_column_index_ == get_num_columns()-1){
            *out_stream_ << "|\n";
            current_row_index_ = current_row_index_ + 1;
            current_column_index_ = 0;
        } else {
            *out_stream_ << separator_;
            current_column_index_ = current_column_index_ + 1;
        }
    }

  std::ostream * out_stream_;
  std::vector<std::string> column_headers_;
  std::vector<int> column_widths_;
  std::string separator_;

  int current_row_index_;
  int current_column_index_;

  int table_width_;
  Alignment alignment_;
};

}

#endif
