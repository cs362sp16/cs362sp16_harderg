DIDNT_RUN = ['-:', '#####:']
FILES = [('unit1', True), ('unit2', False), ('unit3', True), ('unit4', True), ('card1', True),
('card2', True), ('card3', True), ('card4', True), ('random1', True), ('random2', True)]


#Get the number of lines in the file
def get_num_lines(file):
    with open(file, 'r') as f:
        last_line = f.readlines()[-1]
    return int(last_line.split()[1].split(':')[0])

#Get which lines a particular unit test ran
def get_ran_lines(file):
    lines_ran = dict()

    with open(file, 'r') as f:
        line = f.readline()

        while line != '':
            try:
                if line.split()[1][0:2] == '1:':
                    break

            except IndexError:
                pass

            line = f.readline()

        while line != '':
            
            items = line.split()

            try:
                if items[0] not in DIDNT_RUN:
                    lines_ran[items[1].split(':')[0]] = True

            except IndexError:
                pass

            line = f.readline()

    return lines_ran

def get_suspicious_lines(ran_lines, num_lines, n):
    line_suspiciousness = [[i + 1, 0] for i in range(num_lines)]

    passed = sum([1 for i in ran_lines if i[0] == True])
    failed = sum([1 for i in ran_lines if i[0] == False])

    for i in range(len(line_suspiciousness)):

        num_passed = 0
        num_failed = 0

        for test in ran_lines:

            if str(i + 1) in test[1]:
                if test[0]:
                    num_passed += 1 
                else:
                    num_failed += 1

        try:
            f_ratio = (float(num_failed) / float(failed))
            p_ratio = (float(num_passed) / float(passed))
            line_suspiciousness[i][1] = f_ratio / (f_ratio + p_ratio)

        except ZeroDivisionError:
            pass

    return sorted(line_suspiciousness, key=lambda elem: elem[1], reverse=True)[0:n]

def main():
    lines_ran = list()
    num_lines = None

    for output, passed_test in FILES:
        lines_ran.append((passed_test, get_ran_lines(output)))

        if num_lines is None:
            num_lines = get_num_lines(output)

    potential_bug_lines = get_suspicious_lines(lines_ran, num_lines, 100)

    print 'line\t\tsuspiciousness'
    print '\n'.join(['{0:4d}\t\t{1:.02f}'.format(elem[0], elem[1]) for elem in potential_bug_lines])

if __name__ == '__main__':
    main()








