#!/usr/bin/env python3

questions = [

    {   'question': "Who is the current Prime Minister of Canada?",
        'correct': "b",
        'options': [
            "a) Jean Chretien",
            "b) Stephen Harper",
            "c) Cam Guthrie",
            "d) Dalton McGuinty",
            "e) Steve Jobs",
        ],
    },

    {   'question': "Which document outlines the specific rights guaranteed to all Canadian citizens?",
        'correct': "c",
        'options': [
            "a) The Universal Declaration of Human Rights",
            "b) The American Constitution",
            "c) The Canadian Charter of Rights and Freedoms",
            "d) The Ontario Human Rights Code",
            "e) The Convention on the Rights of the child",
        ],
    },

    {   'question': "Which level of government is responsible for Tourism?",
        'correct': "d",
        'options': [
            "a) Municipal",
            "b) Federal",
            "c) Provincial",
            "d) All",
            "e) Legislative",
        ],
    },

    {   'question': "Which of the following is not a Fundamental Freedom?",
        'correct': "a",
        'options': [
            "a) Presumed innocent until proven guilty",
            "b) Conscience and Religion",
            "c) Opinion and Expression",
            "d) Assembly and Association",
            "e) Freedom of peaceful assembly",
        ],
    },

    {   'question': "The three levels of government are Federal, Provincial and ________?",
        'correct': "municipal",
    },

    {   'question': "A two-house system of government is called ________?",
        'correct': "bicameral",
    },

]

right = []
wrong = []

def get_answer(prompt):
    answer = input(prompt).lower()
    while not answer.isalpha():
        answer = input(prompt).lower()
    return answer

def ask_question(qnum, qinfo):
    score = 0
    for tries in range(2):
        fitb = ""
        prompt = "Make your choice: "
        if not qinfo.get('options'):
            fitb = "(Fill in the blank)"
            prompt = "Enter your answer: "
        print("\nQUESTION", qnum, ":", fitb, qinfo['question'])
        if qinfo.get('options'):
            for opt in qinfo['options']:
                print(" ", opt)
        answer = get_answer(prompt)
        if answer == qinfo['correct']:
            print("Correct!")
            score = score + 1
            right.append(qnum)
            break
        else:
            print("False!")
    else:
        wrong.append(qnum)
        print("Out of Chances!")
    return score

def right_wrong(tag, qnos):
    if len(qnos) > 0:
        print("You got these questions", tag, ":")
        for n in range(len(qnos)):
            print(" ", qnos[n], ": ", questions[qnos[n]-1]['question'])

quiz = "'So You Think You Can Civics'"
cont = ""
while cont != "n":
    cont = "n"
    score = 0
    qnum = 0
    right = []
    wrong = []
    print("Welcome to the", quiz, "quiz.")
    print("This quiz will test your knowledge on basic civics topics.")
    print("Let's see if you were paying attention in civics class!")

    num_q = len(questions)
    for qnum in range(num_q):
        score += ask_question(qnum + 1, questions[qnum])

    print("")
    print("Your score is: ", score, "/", num_q)
    percent = (score / num_q) * 100
    print(("Your percentage is: {0:2.0f} ".format(percent)), "%")

    right_wrong("right", right)
    right_wrong("wrong", wrong)

    if score < num_q:
        cont = input("\nContinue (y) or (n): ")

print("\nThanks for completing the", quiz, "quiz!")
