#include "bprinter/table_printer.h"
#include <iomanip>

namespace bprinter {
TablePrinter::TablePrinter(std::ostream * output, const std::string & separator){
  out_stream_ = output;
  i_ = 0;
  j_ = 0;
  separator_ = separator;
  table_width_ = 2; // For the left and right column
}

TablePrinter::~TablePrinter(){

}

int TablePrinter::get_num_columns() const {
  return column_headers_.size();
}

int TablePrinter::get_table_width() const {
  return table_width_;
}

void TablePrinter::set_separator(const std::string &separator){
  separator_ = separator;
}

void TablePrinter::AddColumn(const std::string & header_name, int column_width){
  column_headers_.push_back(header_name);
  column_widths_.push_back(column_width);
  table_width_ += 2;
}

NextLineSymbol TablePrinter::SkipToNextLine(){
  return NextLineSymbol();
}

void TablePrinter::PrintHorizontalLine() {
  for (int i=0; i<table_width_; ++i)
    *out_stream_ << "-";
  *out_stream_ << "\n";
}

void TablePrinter::PrintHeader(){
  PrintHorizontalLine();
  *out_stream_ << "|";

  for (int i=0; i<get_num_columns(); ++i){
    *out_stream_ << column_headers_.at(i);
    if (i != get_num_columns()-1){
      *out_stream_ << separator_;
    }
  }

  *out_stream_ << "|\n";
  PrintHorizontalLine();
}

void TablePrinter::PrintFooter(){
  PrintHorizontalLine();
}

template<>
TablePrinter TablePrinter::operator <<(NextLineSymbol input){
 i_ = i_ + 1;
 j_ = 0;
}

template<typename T>
TablePrinter TablePrinter::operator <<(T input){
  *out_stream_ << std::setw(column_widths_.at(j_)) << input;

  if (j_ == get_num_columns()-1){
    *out_stream_ << "|\n";
    i_ = i_ + 1;
    j_ = 0;
  } else {
    *out_stream_ << separator_;
    j_ = j_ + 1;
  }
}

}
