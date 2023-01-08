#include <stdio.h>
#include <string.h>
#include <stdbool.h>


bool is_digit(int character){
    return character >= '0' && character <= '9';
}

bool is_letter(int character){
    return ( character >= 'A' && character <= 'Z' ) || ( character >= 'a' && character <= 'z' );
}

bool is_special_char(int character){
    char special_chars[] = "!%()*+-.,/^ ";
    for (int i = 0; special_chars[i] != '\0'; i++){
        if (character == special_chars[i]){
            return true;
        }
    }
    return false;
}


bool sanitize_input(const char* input, char* parsed_input){

    for (int i = 0; input[i] != '\0'; i++){

        char tmpstr[1];
        tmpstr[0] = input[i];

        if ( !is_digit(input[i]) && !is_letter(input[i]) && !is_special_char(input[i]) ){
            return false;

        }

        else if (input[i] != ' '){
            strcat(parsed_input, tmpstr); 
        }

    }
    return true;
}

int split_layer(char* layer, char* expr1, char* expr2, int operator_index){

    int k = 0;

    for (int i = 0; layer[i] != '\0'; i++){

        if ( i < operator_index){
            expr1[i] = layer[i]; 
        }
        else if ( i > operator_index) {
            expr2[k] = layer[i];
            k++;
        }
    }

    return 0;

}

bool is_numerical(char* expression){

    for (int i = 0; expression[i] != '\0'; i++){
        if( !is_digit(expression[i]) && (expression[i] != '.')){
            return false;
        }
    }

    return true;

}

bool is_elementary(char* expression){

    if (expression[0] == 'x' && expression[1] == '\0'){

        expression[0] = '2';

        return true;

    }
    else if (is_numerical(expression)){
        return true;
    }
    else{
        return false;
    }


}

double evaluate_layer(double x, double y, char operaattori){


    switch (operaattori) {
        case '+':
            return x + y;
            break;
        case '-':
            return x - y;
            break;
        case '*':
            return x * y;
            break;
        case '/':
            return x / y;
            break;
        default:
            // operator is doesn't match any case constant (+, -, *, /)
            //std::cout << "Error! The operator is not correct";
            return 0;
            break;
    }    
}

//run over parantheses, check if elementary and check if mismatched parantheses
//std::vector<string>
double parse_layer(char* layer){


    double x;
    double z;

    char operators[] = "+-*/^";

    int paranthese_amount = 0;

    for (int k = 0; operators[k] != '\0'; k++){

        for (int i = 0; layer[i] != '\0'; i++){

            if (layer[i] == '('){

                paranthese_amount++;

                while( paranthese_amount != 0){

                    i++;

                    if (layer[i] == ')'){
                        paranthese_amount--;
                    }
                    else if (layer[i] == '('){

                        paranthese_amount++;

                    }
                }
            }
            else if (layer[i] == operators[k]){

                //if not elementary
                char expr1[strlen(layer)];                
                char expr2[strlen(layer)];                
                memset( expr1, 0, strlen(layer)*sizeof(int) );
                memset( expr2, 0, strlen(layer)*sizeof(int) );


                split_layer(layer, expr1, expr2, i);


                if (!is_elementary(expr1)){
                    x = parse_layer(expr1);
                }
                else{
                    sscanf(expr1, "%lf", &x);
                }

                if (!is_elementary(expr2)){
                    z = parse_layer(expr2);
                }
                else{

                    sscanf(expr2, "%lf", &z);

                }

                //std::cout << x << " ; " << z << " ; " << operators[k] << std::endl;

                return evaluate_layer(x, z, operators[k]);

            }

        }


    }
        if(layer[0] == '(' && layer[strlen(layer) - 1] == ')'){


            for( int j = 1; j < strlen(layer); j++){

                layer[j-1] = layer[j];
            }

            layer[strlen(layer) - 2] = '\0';
            return parse_layer(layer);
        }
    return 0;
}

int main(int argc, char *argv[]){

        double result = parse_layer(argv[1]);
        printf ("result: %f", result);

        return 0;

}
