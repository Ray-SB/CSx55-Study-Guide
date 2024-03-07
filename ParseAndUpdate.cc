
# include <iostream>
# include <fstream>
# include <string>
# include <vector>
# include <sstream>
# include <algorithm>

using namespace std;

// check if line is a question
bool isQuestionBlock(string line) {
  return line.find("Results for question") != string::npos;
}

// parse quiz file and return vector of questions and answers
vector<array<string, 2>> parseQuizResults(string filename) {

  ifstream file(filename);
  string line;
  vector<array<string, 2>> results;

  while (getline(file, line)) {

    // enter a question block
    if (isQuestionBlock(line)) {

      // skip until after " point"
      while (getline(file, line))
        if (line.find(" point") < line.size() && line.size() != 0) {
          getline(file, line);
          break;
        }

      // get question
      getline(file, line);
      string question = line;
      cout << "QUESTION: " << question << "\n";

      // skip until "Correct Answer:"
      while (getline(file, line))
        if (line.find("Correct Answer:") < line.size() && line.size() != 0) {
          break;
        }

      // get answer by splicing after "Correct Answer:"
      string answer = line.substr(15);
      cout << "ANSWER: " << answer << "\n\n";

      // add question and answer to results
      results.push_back({question, answer});
    }
  }

  return results;
}



int main(int argc, char **argv) {

  if (argc < 3) {
    cout << "usage: " << argv[0] << " <quiz file> <results file>\n";
    return 1;
  }

  string quizFile = argv[1];
  string resultsFile = argv[2];

  vector<array<string, 2>> results = parseQuizResults(quizFile);

  // print results
  for (auto result : results) {
    cout << "QUESTION:\n" << result[0] << "\nANSWER:\n" << result[1] << "\n\n";
  }

}
