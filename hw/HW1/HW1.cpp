#include <iostream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>

//error fuction

void errors(std::vector<std::string> inputs){

//since input 1 and 2 are already checked at this point, the code doesn't check it
//puts input 3 into a string and checks each character in the string to see if it is a digit.
//if it is ever false == false, exit

    std::string number = inputs[3];
    int number_length = number.length();
    for (int i = 0; i < number_length; i++){
        if (isdigit(number[i]) == false){
            std::cerr << "Not a valid width" << std::endl;
            exit(1);
        }
    }

//checks input 4. if the string isn't flush_left, flush_right or full_justify, then print error message
//exit

    std::string just = inputs[4];
    if (just != "flush_left" && just != "flush_right" && just != "full_justify"){
        std::cerr << "Not a real justify" << std::endl;
        exit(1);
    }
}

//splits up a word into 2 based on its width. outputs a vector with its elements being the first half
//of the word and the second element being the second half of the world the first half will have a '-'
//at the end of the word

std::vector<std::string> longer_than_width(std::string word, int width){
    std::vector<std::string> split_word;
    std::string first_half = word.substr(0, width-1) + '-';
    split_word.push_back(first_half);
    std::string second_half = word.substr(width-1);
    split_word.push_back(second_half);
    return split_word;
}

//puts the word from the text file into lines easy to manipulate. it also uses the longer_than_width
//function if a word is longer than the width

std::vector<std::string> into_lines(std::vector<std::string> text, unsigned int width){
    //this vector will hold the lines of the words created
    std::vector<std::string> new_text;
    //the size of the text given
    int vector_size = text.size();
    //all words and spaces will be concatenated into this string
    std::string line_string = "";
    //goes through each word in the text
    for ( int i = 0 ; i < vector_size; i++){
        //if this is the first word in the text, just put it into the front of line_string
        if (i == 0){
            int text_length = text[i].length();
            //if the word is longer than the width use the longer_than_width
            //put into a while loop until the word is less than the width
            if (text_length > width){
                while (text_length > width){
                    std::vector<std::string> split_word = longer_than_width(text[i], width);
                    new_text.push_back(split_word[0]);
                    text[i] = split_word[1];
                    text_length = text[i].length();
                }
            } 
            line_string = text[i];
            continue;
            
        }
        //concatenate a space than a word into line_string. if a word were to be placed into line_string
        //and it exceeds width, push back and line_string will become the word
        if ((line_string + ' ' +text[i]).length() <= width){
            line_string = line_string + ' ' + text[i];
        } else {
            new_text.push_back(line_string);
            //test if the new word is longer than width
            int text_length = text[i].length();
            if (text_length > width){
                while (text_length > width){
                    std::vector<std::string> split_word = longer_than_width(text[i], width);
                    new_text.push_back(split_word[0]);
                    text[i] = split_word[1];
                    text_length = text[i].length();
                }
            }
            line_string = text[i];
            continue;
        
        }
    }
    //return the new text amde
    new_text.push_back(line_string);
    return new_text;
}

//left justify by adding spaces until the length hits the width

std::vector<std::string> left_just(std::vector<std::string> new_text, int width){
    int new_text_size = new_text.size();
    int extra_space;
    //calcuate the extra spaces for every line
    for ( int i = 0; i < new_text_size; i++){
        extra_space = width - new_text[i].length();
        //for every extra space add a space to the back of the line
        for ( int j = 0; j < extra_space; j++){
            new_text[i] = new_text[i] + ' ';
        }
    }
    return new_text;
}

//right justify by adding spaces until the length hits the width

std::vector<std::string> right_just(std::vector<std::string> new_text, int width){
    int new_text_size = new_text.size();
    int extra_space;
    //calculate the extra spaces
    for (int i = 0; i < new_text_size; i++){
        extra_space = width - new_text[i].length();
        //for every extra space add spaces to the front of the line
        for (int j = 0; j < extra_space; j++){
            new_text[i] = ' ' + new_text[i];
        }
    }
    return new_text;
}

//full justify calculate the extra spaces and evenly distibute the spaces among the words

std::vector<std::string> full_just(std::vector<std::string> new_text, int width){
    int new_text_size = new_text.size();
    //extra spaces are the extra spaces needed to hit the width, how_many_spaces counts the number 
    //of spaces already there. evenly spaces are the number of extra spaces each existing space
    //will get. remainder spaces are spaces put to the most left existing space
    int extra_spaces;
    int how_many_spaces;
    int evenly_spaces;
    int remainder_spaces;
    char space = ' ';
    //for each line in the vector
    for (int i = 0; i < new_text_size; i++){
        extra_spaces = width - new_text[i].length();
        how_many_spaces = std::count( new_text[i].begin(), new_text[i].end(), ' ');
        //if this is the last line, just left justify
        if (i == new_text_size-1){
            for ( int j = 0; j < extra_spaces; j++){
                new_text[i] = new_text[i] + ' ';
            } 
            continue;           
        }
        //if how_many_spaces are 0 there are no existing spaces so just left justify
        if (how_many_spaces == 0){
            for ( int j = 0; j < extra_spaces; j++){
                new_text[i] = new_text[i] + ' ';
            }
            
        } else {    
            //number_of_spaces vector holds the number of extra spaces needed for each existing space        
            std::vector<int> number_of_spaces;
            evenly_spaces = extra_spaces / how_many_spaces;
            remainder_spaces = extra_spaces % how_many_spaces;
            //push back the int evenly spaces by how_many_space
            for (int j = 0; j < how_many_spaces; j++){
                number_of_spaces.push_back(evenly_spaces);
            }
            //for each reaminder spacce, just add 1 to the left most vector index
            for (int k = 0; k < remainder_spaces; k++){
                number_of_spaces[k]++;
            }
            int number_of_spaces_size = number_of_spaces.size();
            //use .find  to find where the space is starting from 0
            int location = new_text[i].find(space);
            //for each index in the vector
            for (int L = 0; L < number_of_spaces_size; L++){
                //for each int, add the number of spaces in temp_spaces
                std::string temp_spaces = "";
                for (int m = 0; m < number_of_spaces[L]; m++){
                    temp_spaces = temp_spaces + ' ';
                }
                //each index in new_text becomes original text to location, add extra spaces, rest of 
                //text
                new_text[i] = new_text[i].substr(0, location) + temp_spaces + new_text[i].substr(location);
                //with the new text, find the next location by adding the original location, number of spaces
                //and 1
                location = new_text[i].find(space, location + number_of_spaces[L] + 1);
            }
        }
    }
    return new_text;
}

//main

int main( int argc, char* argv[]){

//puts the inputs into a vector and uses the errors function. will exit if it finds any errors.
    std::vector<std::string> input_strings;
    for (int i = 0; i < argc; i++){
        input_strings.push_back(argv[i]);
    }
    errors(input_strings);

//code for reading text files and testing if the file exists.

    std::ifstream in_str(argv[1]);
      if (!in_str.good()) {
        std::cerr << "Can't open " << argv[1] << " to read.\n";
        exit(1);
    }

//this variable will contain most of the data for this code

    std::vector<std::string> input;

//code for writing into a text file and testing if the text file exist. I copied the code from submitty
//but it doesn't work. It creates new text files when I dont want to but it writes on existing files.

    std::ofstream out_str(argv[2]);
    if (!out_str.good()) {
        std::cerr << "Can't open " << argv[2] << " to write.\n";
        exit(1);
    }

    int width = atoi(argv[3]);
    std::string justification = argv[4];

//put words read from the file into input variable

    std::string temp;
    while (in_str >> temp){
        input.push_back(temp);
    }

//use into_lines to put the words read into lines based on the width given

    input = into_lines(input, width);

//depending on the flush given, it will use different fuctions to flush the lines made earlier

    if (justification == "flush_left"){
        input = left_just(input, width);
    } else if (justification == "flush_right"){
        input = right_just(input, width);
    } else {
        input = full_just(input, width);
    }

//writes the top of the box

    for (int i = 0; i < width+4; i++){
        out_str << '-';
    }
    out_str << std::endl;

//loops through input variable and writes into text file
    
    int text_rows = input.size();
    for (int i = 0; i < text_rows; i++){
        out_str << "| " << input[i] << " |" << std::endl;
    }

//writes the bottom of the box (same code for the top of the box)
    
    for (int i = 0; i < width+4; i++){
        out_str << '-';
    }
    out_str << std::endl;
    return 0;
}