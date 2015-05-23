cont = ""

questions = [
    "What is the Zeroth Law of Thermodynamics?",
    "Who is the current Prime Minister of Canada?",
    "Which document outlines the specific rights guaranteed to all Canadian citizens?",
    "Which level of government is responsible for Tourism?",
    "Which of the following is not a Fundamental Freedom?",
    "(Fill in the blank) The three levels of government are Federal, Provincial and _______?",
    "(Fill in the blank) A two-house system of government is called ________?",
]

def get_answer(prompt):
    answer = input(prompt).lower()
    while not answer.isalpha():
        answer = input(prompt).lower()
    return answer

while cont != "n":
    score = 0
    qnum = 0
    right = []
    wrong = []
    print("Welcome to the 'So You Think You Can Civics' quiz.")
    print("This quiz will test your knowledge on basic civics topics.")
    print("Let's see if you were paying attention in Civics class!")

    qnum = qnum + 1
    for tries in range(2):
        print("\nQUESTION ", qnum, ":\n", questions[qnum])
        print(" a) Jean Chretien", "\n","b) Stephen Harper", "\n", "c) Cam Guthrie", "\n", "d) Dalton McGuinty", "\n", "e) Steve Jobs")
        answer = get_answer("Make your choice: ")
        if answer == "b":
            print("Correct!")
            score = score + 1
            right.append(qnum)
            break
        else:
            print("False!")
    else:
        wrong.append(qnum)
        print("Out of Chances!")

    qnum = qnum + 1
    for tries in range(2):
        print("\nQUESTION ", qnum, ":\n", questions[qnum])
        print(" a) The Universal Declaration of Human Rights", "\n", "b) The American Constitution", "\n", "c) The Canadian Charter of Rights and Freedoms", "\n", "d) The Ontario Human Rights Code", "\n", "e) The Convention on the Rights of the child")
        answer = get_answer("Make your choice: ")
        if answer == "c":
            print("Correct!")
            score = score + 1
            right.append(qnum)
            break
        else:
            print("False!")
    else:
        print("Out of Chances!")
        wrong.append(qnum)

    qnum = qnum + 1
    for tries in range(2):
        print("\nQUESTION ", qnum, ":\n", questions[qnum])
        print(" a) Municipal\n", "b) Federal\n", "c) Provincial\n", "d) All\n", "e) Legislative")
        answer = get_answer("Make your choice: ")
        if answer == "d":
            print("Correct!")
            score = score + 1
            right.append(qnum)
            break
        else:
            print("False!")
    else:
        print("Out of Chances!")
        wrong.append(qnum)

    qnum = qnum + 1
    for tries in range(2):
        print("\nQUESTION ", qnum, ":\n", questions[qnum])
        print(" a) Presumed innocent until proven guilty", "\n", "b) Conscience and Religion", "\n", "c) Opinion and Expression", "\n", "d) Assembly and Association", "\n", "e) Freedom of peaceful assembly")
        answer = get_answer("Make your choice: ")
        if answer == "a":
            print("Correct!")
            score = score + 1
            right.append(qnum)
            break
        else:
            print("False!")
    else:
        print("Out of Chances!")
        wrong.append(qnum)

    qnum = qnum + 1
    for tries in range(2):
        print("\nQUESTION ", qnum, ":\n", questions[qnum])
        answer = get_answer("Enter your answer: ")
        if answer == "municipal":
            print("Correct!")
            score = score + 1
            right.append(qnum)
            break
        else:
            print("False!")
    else:
        print("Out of Chances!")
        wrong.append(qnum)

    qnum = qnum + 1
    for tries in range(2):
        print("\nQUESTION ", qnum, ":\n", questions[qnum])
        answer = get_answer("Enter your answer: ")
        if answer == "bicameral":
            print("Correct!")
            score = score + 1
            right.append(qnum)
            break
        else:
            print("False!")
    else:
        print("Out of Chances!")
        wrong.append(qnum)

    print("Your score is: ", score,"/6")
    percent = (score/6)*100
    print(("Your percentage is:{0:2.0f} ".format(percent)),"%")

    if len(right) > 0:
        print("You got these questions right:")
        for r in range(len(right)):
            print(" ", right[r], ": ", questions[right[r]])

    if len(wrong) > 0:
        print("You got these questions wrong:")
        for w in range(len(wrong)):
            print(" ", wrong[w], ": ", questions[wrong[w]])

    cont = input("Continue (y) or (n):")

print("\nThanks for completing the 'So You Think You Can Civics' quiz!")
