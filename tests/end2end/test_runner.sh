#!/bin/bash


#color atributes
red="\033[1;31m"
green="\033[1;32m"
blue="\033[1;36m"
purple="\033[1;35m"
white="\033[1;37m"
usual="\033[0m"
#directories paths and exe file for test generating
resource_dir="../tests/end2end/resources/"
tests_dir="../tests/end2end/resources/tests/"
answs_dir="../tests/end2end/resources/answers/"
exe_test_file="./tests/end2end"
exe_main_file="./matrix"

##------------------------------------------------------------------------------------------##
function run_tests {
    generate_tests

    touch compare_file.txt
    if [ -d "${resource_dir}" ]
    then
        echo -e "${white}---end2end testing---${usual}"
        for ((i = 1; i <= ${tests_number}; ++i))
        do      
                tmp_check=${tests_dir}/test${i}.txt
                ${exe_main_file} < ${tmp_check} > compare_file.txt

                echo -n -e "${purple}Test ${i}: ${usual}\n"
                ans_file="${answs_dir}answ${i}.txt"
                if diff -w -n ${ans_file} compare_file.txt &>/dev/null
                then
                    echo -e "${green}passed${usual}" 
                else
                    echo -e "${red}failed${usual}"
                fi
                echo -en "${blue}determinant:${usual}"
                printf "\n"
                cat ${ans_file}
                printf "\n"
        done
    else
        echo -e "${blue}can't generate tests. ${usual}${resource_dir} is empty"
    fi

    rm compare_file.txt
}
##------------------------------------------------------------------------------------------##

##------------------------------------------------------------------------------------------##
function generate_tests {
    def_file_name="test"
    for ((i = 1; i <= ${tests_number}; ++i))
    do
        ${exe_test_file} ${tests_number} ${matrix_size} ${max_determ}
    done

}
##------------------------------------------------------------------------------------------##

#main part
error="false"
tests_number=0
matrix_size=0
max_determ=1

if [ $# -eq 3 ]
then
    tests_number=$1
    matrix_size=$2
    max_determ=$3
else
    error="true"
    echo -e "${red}invalid number of arguments: expected 3, got $#"
fi

if [ $error = "false" ]
then
    run_tests 
fi

