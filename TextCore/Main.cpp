#include "stdafx.h"

using std::string;
using std::cout;

struct WordInfo {
    WordInfo() :n(0) {}
    int n;
    std::vector<const string> words_list;
};

std::unordered_map<string, /*std::vector<const string>*/WordInfo> WordsTable;

// add: add word to suffix vector
void add(const string& curr_word) {
    static string prev_word;

    ++WordsTable[prev_word].n;
    WordsTable.at(prev_word).words_list.push_back(curr_word);

    prev_word = curr_word;
}


// build: read input words, build state table
void build(std::istream& in) {
    string buff;

    while (in >> buff) {
        boost::trim_right_if(buff, boost::is_any_of(",0123456789-<>:\""));
        if (buff.size() < 1)
            continue;
        boost::trim_left_if(buff, boost::is_any_of(",-<>:\""));
        if (buff.size() < 1)
            continue;

        if (buff.find_last_of("?") == buff.size() - 1) {
            boost::trim_right_if(buff, boost::is_any_of(" ?"));
            if (buff.size() >= 1) {
                add(buff);
                add("?");
            }
            continue;
        }

        if (buff.find_last_of("!") == buff.size() - 1) {
            boost::trim_right_if(buff, boost::is_any_of(" !"));
            if (buff.size() >= 1) {
                add(buff);
                add("!");
            }
            continue;
        }

        if (buff.find_last_of(".") == buff.size() - 1) {
            boost::trim_right_if(buff, boost::is_any_of(" ."));
            if (buff.size() >= 1) {
                add(buff);
                add(".");
            }
            continue;
        }

        if (buff.find_first_of("0123456789") == string::npos && buff.size() >= 1)
            add(buff);
    }
}

int getFile(const TCHAR* fileName) {
    std::ifstream input_file_stream(fileName);
    if (!input_file_stream.is_open( )) {
        std::cerr << "ERROR file not opened";
        return -1;
    }
    build(input_file_stream);
    input_file_stream.close();

    return 0;
}

void view_table() {
    std::ifstream skipfile_stream("skip.txt");
    if (skipfile_stream.fail())
        std::cerr << "\nWARNING: Skip file not opened.\n";

    const std::istream_iterator<string> ii(skipfile_stream);
    std::istream_iterator<string> eos;

    std::vector<string> skipwords(ii, eos);

    //int i = 0;
    typedef std::multimap<int, string> word_index;
    word_index words_by_freq;
    for (const auto &state : WordsTable) {
        words_by_freq.insert(std::pair<int, string>(state.second.n, state.first));
    }

    word_index::const_reverse_iterator it;
    int j = 0;
    for (it = words_by_freq.rbegin(); it != words_by_freq.rend(); ++it) {
        bool skip_detected = false;
        for (auto &x : skipwords) {
            if (x == it->second) {
                skip_detected = true;
                break;
            }
        }
        if (skip_detected) {
            continue;
        }
        if (it->second == "." || it->second == "!" || it->second == "?")
            continue;
        cout << "\t" << it->first << ' ' << it->second << ": \t";

        for (const auto &word : WordsTable.at(it->second).words_list) {
            cout << word << " ";
        }
        cout << "\n";
        if (++j > 15)
            break;
    }



#if 0
    for (const auto &markov_state : statetab) {
        //const auto& suffixes = markov_state.second;
        /*
        if (suffixes.size() == 1 )
        continue;
        */
        const auto& prefix = markov_state.first;
        cout << prefix;// << " \x04 ";
        cout << " (" << markov_state.second.n << ") ";
        cout << "\t\x1A ";// << x.second.capacity() << "  " << x.second.size() << "    ";
        for (const auto &word : markov_state.second.words_list) {
            cout << word << " ";
        }
        cout << "\n";
        if (++i > 20)
            break;
    }
#endif
}

