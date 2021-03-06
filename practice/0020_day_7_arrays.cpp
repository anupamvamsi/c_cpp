#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split_string(std::string);

int main() {
  int n;
  std::cin >> n;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  // <streamsize> is a data type (signed integer)
  // numeric_limits is a class template
  // largest possible value for type `int` is numeric_limits<int>::max()
  // numeric_limits<streamsize> ≡ vector<int>
  // https://en.cppreference.com/w/cpp/types/numeric_limits

  std::string arr_temp_temp;
  std::getline(std::cin, arr_temp_temp);

  std::vector<std::string> arr_temp = split_string(arr_temp_temp);

  std::vector<int> arr(n);

  for (int i = 0; i < n; i++) {
    int arr_item = stoi(arr_temp[i]);

    arr[i] = arr_item;

    // std::cout << arr[i] << " ";
  }

  // the part I wrote - anupam
  for (int i = 0; i < n; i++) {
    std::cout << arr[n - 1 - i] << " ";
  }
  //

  return 0;
}

std::vector<std::string> split_string(std::string input_string) {
  std::string::iterator new_end =
      unique(input_string.begin(), input_string.end(),
             [](const char &x, const char &y) { return x == y && x == ' '; });

  input_string.erase(new_end, input_string.end());

  while (input_string[input_string.length() - 1] == ' ') {
    input_string.pop_back();
  }

  std::vector<std::string> splits;
  char delimiter = ' ';

  size_t i = 0;
  size_t pos = input_string.find(delimiter);

  while (pos != std::string::npos) {
    splits.push_back(input_string.substr(i, pos - i));

    i = pos + 1;
    pos = input_string.find(delimiter, i);
  }

  splits.push_back(
      input_string.substr(i, std::min(pos, input_string.length()) - i + 1));

  return splits;
}
