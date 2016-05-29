#!/usr/bin/python
# -*- coding: utf-8 -*-
#
# Made by duponc_j@epitech.net
#
# Modified by flavien.maillot@epitech.eu
#
# Version: 1.3.1
# Annee 2014

'''
An Epitech norme checker

Bug:
Il est arrivee que le checker ne trouve aucune faute alors qu\'il en existe, si
ce bug vous arrive envoyez moi un e-mail.
'''

import sys,re,os,pwd,urllib2

version = "1.3.1"

class norme:
    def __init__(self):
        self.user = []
        self.verbose = 0
        self.cheat = 0
        self.comment = 1
        self.score = 1
        self.note = 0
        self.libc = 1
        self.printline = 0
        self.creturn = 1

    def new_file(self):
        self.nb_line = 1
        self.nb_return = 0
        self.nb_funcline = 0
        self.nb_func = 0
        self.sys_include = 0
        self.double_inclusion = 0
        self.declaration_jump = 0
        self.is_func = 0
        self.typedef = 0
        self.indent = [0, 0, 0]
        self.intype = []
        if self.verbose == 1:
            print "Scan",self.file

    def check_header(self):
        if (self.nb_line == 1):
            if (self.line[:2] != '/*' and self.line[:2] != '/*\n'):
                efbbbf = u"\uFEFF"
                if (self.line[:3] == efbbbf.encode('UTF-8')):
                    self.line[:5]
                    self.print_error('Zero-width no-break space trouvé au début du header')
                else:
                    self.print_error('Début de header incorrect')
                    self.note += 20
        elif (self.nb_line == 9):
            if (self.line[:2] != '*/'):
                self.print_error('Fin de header incorrect :')
        elif self.nb_line == 4 or self.nb_line == 7 or self.nb_line == 8:
            if self.cheat:
                p = re.compile('(\*\* Made by )([\w -]*)$')
                test = re.search(p, self.line)
                if test:
                    if not test.group(2) in self.user:
                        self.print_error('Ce fichier appartient à '+ test.group(2))
                        print "\033[0;35;40mRisque -42 pour triche.\n\033[0m"
        elif (self.nb_line == 5):
            if self.cheat:
                p = re.compile('<(.*)@')
                test = re.search(p, self.line)
                if test:
                    if not test.group(1) in self.user:
                        self.print_error('Le login '+ test.group(1) +' ne correspond pas à celui de la session en cours...')
                        print "\033[0;35;40mRisque -42 pour triche.\033[0m"
                        sys.exit()
        else:
            if (self.line[:2] != '**'):
                self.print_error('Header incorrect')

    def check_indent_line(self):
        if (self.line[:1] == '\n'):
            return True
        if (self.indent[0] == 0 and self.indent[1] == 0):
            return False
        p = re.compile('^([\t]{'+ str(self.indent[0]) +'}[ ]{'+ str(self.indent[1]) +'})(?![ \t])')
        test = re.search(p, self.line)
        if test is None:
            if self.indent[2] != 0:
                self.indent[2] +=  self.line.count('(')
                self.indent[2] -=  self.line.count(')')
                return True
            msg = 'Erreur d\'indentation, il doit y avoir ' + str(self.indent[0]) + ' tabulation(s) et ' + str(self.indent[1]) + ' espace(s)'
            self.print_error(msg)
            self.note += 1
        return False

    def add_space_or_tab(self):
        if (self.indent[1] + 2 > 6):
            self.indent[0] += 1
            self.indent[1] = 0
        else:
            self.indent[1] += 2

    def remove_space_or_tab(self):
        if (self.indent[1] - 2 < 0):
            if (self.indent[0] > 0):
                self.indent[0] -= 1
                self.indent[1] = 6
        else:
            self.indent[1] -= 2

    def check_indent(self):
        if is_close_brace(self.line) == True:
            if (len(self.intype) > 1):
                if (self.intype[-1] != 2):
                    while (self.intype[-1] != 2):
                        self.remove_space_or_tab()
                        self.intype.pop()
                    self.remove_space_or_tab()

                    self.intype.pop()
                else:
                    self.intype.pop()
                    self.remove_space_or_tab()
            else:
                self.intype.pop()
                self.remove_space_or_tab()
        if self.check_indent_line() == True:
            return True
        if (self.indent[0] != 0 and self.indent[1] != 0):
            if is_close_brace(self.line) == True:
                self.intype.pop()
                self.remove_space_or_tab()
                return True
        if is_indent_key(self.line) == True:
            self.indent[2] = self.line.count('(')
            self.indent[2] -= self.line.count(')')
            self.intype.append(1)
            self.add_space_or_tab()
            return True
        if is_open_brace(self.line) == True:
            self.intype.append(2)
            self.add_space_or_tab()
            return True
        if (len(self.intype) > 1):
            if (self.intype[-1] != 2):
                while (self.intype[-1] != 2):
                    self.remove_space_or_tab()
                    self.intype.pop()

    def check_virgule(self):
        if is_commented(self.line) == False:
            n = 0
            quote = 0
            while self.line[n] != '\n':
                if self.line[n] == '\'' or self.line[n] == '"' and self.line[n - 1] != '\\':
                    if quote:
                        quote = 0
                    else:
                        quote = 1
                if (self.line[n] == ';' or self.line[n] == ',') and quote == 0:
                    if self.line[n + 1] != ' ' and self.line[n + 1] != '\n':
                        self.note += 1
                        self.print_error('Point-virgule ou virgule mal placé')
                n = n + 1


    def check_nbchar(self):
        line = self.line.replace('\t', '    ')
        if (line[80:]):
            self.note += 1
            self.print_error('Chaine de plus de 80 caractères')

    def check_return(self):
        if (self.line[:1] == '\n'):
            if (self.nb_return == 1):
                self.note += 1
                self.print_error('Double retour à la ligne')
            else:
                self.nb_return = 1
        else:
            self.nb_return = 0

    def check_nbline(self):
        if self.file[-2:] == ".c":
            if self.line[:1] == '}':
                self.is_func = 0
                self.nb_funcline = 0
            if self.line[:1] == '{' and self.typedef == 0:
                self.is_func = 1
                self.nb_funcline = 0
                self.nb_func = self.nb_func + 1
                if self.nb_func == 6:
                    self.note += 1
                    self.print_error('Plus de 5 fonctions dans le fichier')
            else:
                if self.nb_func >= 1 and self.is_func:
                    self.nb_funcline = self.nb_funcline + 1
                    if self.nb_funcline >= 26 and self.is_func == 1:
                        self.note += 1
                        self.is_func = 2
                        self.print_error('Fonction de plus de 25 lignes')

    def check_cfunc(self):
        if is_commented(self.line) == False:
            p = re.compile('[ \t](if|else|return|while|for)(\()')
            test = re.search(p, self.line)
            if test:
                self.note += 1
                self.print_error('Manque un espace après le mot clé ' + test.group(1))

    def check_arg(self):
        if self.line[-2:] == ")\n" and self.line[:1] != '\t'  and self.line[:1] != ' ':
            p = re.compile('(.*),(.*),(.*),(.*),(.*)\)$')
            test = re.search(p, self.line)
            if test:
                self.note += 1
                self.print_error('Plus de 4 arguments passés en paramètre')

    def check_sys_include(self):
        if self.line[:1] == "#" and self.line[-2:] == "\"\n":
            self.sys_include = 1
        else:
            if self.line[:1] == "#" and self.line[-2:] == ">\n" and self.sys_include == 1:
                self.note += 1
                self.print_error('Header système mal placé')

    def check_comment(self):
        if self.is_func and self.comment:
            p = re.compile('(//|/\*)')
            test = re.search(p, self.line)
            if test:
                self.note += 1
                self.print_error('Commentaires dans le code')

    def check_malloc(self):
        p = re.compile('[^x](malloc)(\()')
        test = re.search(p, self.line)
        if test and (self.file != "xmalloc.c"):
            self.print_error('Malloc non verifiée')
            self.note += 1

    def check_tabulation(self):
        p = re.compile('(static|ssize_t|size_t|pid_t|(t_[a-z]{2,})|unsigned|int|char|void|float|double|short|long)(  )')
        test = re.search(p, self.line)
        if test:
            self.print_error('Erreur de tabulation');
            self.note += 1

    def check_jump_after_d(self):
        p = re.compile('^([\} \t]*)(static|ssize_t|size_t|pid_t|(t_[a-z]{2,})|unsigned|int|char|void|float|double|short|long)([ ]|[\t])+(.*)(;\n)')
        test = re.search(p, self.line)
        if test:
            self.declaration_jump = 1
        else:
            p = re.compile('^([\} \t]*)(})([ ]|[\t])*(.*)(;\n)')
            test = re.search(p, self.line)
            if test:
                self.declaration_jump = 1
            elif (self.declaration_jump == 1):
                self.declaration_jump = 0
                if self.line[:1] != "\n":
                    self.print_error('Manque un retour de ligne juste avant :');
                    self.note += 1

    def check_declaration_unique(self):
        p = re.compile('^([ \t]*)(int|char|void|float|double|short|long){1}([A-Za-z0-9\s_\*]*[,]+)(.*)(;{1})')
        test = re.search(p, self.line)
        if test:
            self.print_error('Plusieurs déclarations sur la même ligne');
            self.note += 1

    def check_operateur(self, op):
        n = 0
        quote = 0
        while self.line[n] != '\n':
            if self.line[n] == '\'' or self.line[n] == '"' and self.line[n - 1] != '\\':
                if quote:
                    quote = 0
                else:
                    quote = 1
            if (self.line[n] == op) and quote == 0:
                if self.line[n + 1] != ' ' and self.line[n + 1] != ';' and self.line[n + 1] != '=' and self.line[n + 1] != '\n':
                    if self.line[n - 1] != op and self.line[n + 1] != op:
                        msg = 'Operateur %c mal placé' % op
                        self.print_error(msg)
                        self.note += 1
            n = n + 1

    def check_typedef(self):
        if self.line[:7] == "typedef":
            self.typedef = 1
        else:
            self.typedef = 0

    def check_regex(self, regex, msg):
        p = re.compile(regex)
        test = re.search(p, self.line)
        if test:
            self.note += 1
            self.print_error(msg)

    def check_line(self):
        if is_commented(self.line) == False:
            self.check_nbline()
            self.check_sys_include()
            self.check_virgule()
            self.check_regex('[ \t]$', 'Espace en fin de ligne')
            if self.creturn == 0:
                self.check_regex('return( \(\)| ;|;)', 'Mauvais format de return')
            if self.libc == 0:
                self.check_regex('[^_](printf|atof|atoi|atol|strcmp|strlen|strcat|strncat|strncmp|strcpy|strncpy|fprintf|strstr|strtoc|sprintf|asprintf|perror|strtod|strtol|strtoul)(\()', \
                             'Fonction de la lib C')
            self.check_nbchar()
            self.check_cfunc()
            self.check_arg()
            self.check_comment()
            self.check_return()
            self.check_tabulation()
            self.check_declaration_unique()
            self.check_indent()
            self.check_jump_after_d()
            self.check_operateur('+')
            self.check_operateur('|')
            self.check_typedef()

    def print_error(self, msg):
        print "Erreur dans",self.file,"à la ligne",self.nb_line,":\n\033[0;31;40m",msg,"\033[0;m"
        if self.printline:
            print "\033[0;33;40m",self.line,"\033[0;m"

    def cant_open(self, file):
        if (self.verbose or file == sys.argv[1]):
            print "Impossible d'ouvrir",file

    def scan_files(self, files):
        for file_name in files:
            self.file = file_name
            self.new_file()
            try:
                fd = open(file_name, 'r')
            except IOError:
                self.cant_open(file)
            else:
                for self.line in fd.readlines():
                    if self.nb_line <= 9:
                        self.check_header()
                    else:
                        self.check_line()
                    self.nb_line = self.nb_line + 1
                    fd.close()

    def scandir(self, thedir):
        try:
            dir = os.listdir(thedir)
        except:
            self.cant_open(thedir)
        else:
            check_makefile(thedir)
            for file in dir:
                if (os.path.isdir(thedir + file)):
                    self.scandir(thedir + "/" + file + "/")
                if file[-2:] == '.c' or file[-2:] == '.h':
                    self.file = file
                    self.new_file()
                    file = thedir + file
                    try:
                        fd = open(file, 'r')
                    except IOError:
                        self.cant_open(file)
                    else:
                        for self.line in fd.readlines():
                            if self.nb_line <= 9:
                                self.check_header()
                            else:
                                self.check_line()
                            self.nb_line = self.nb_line + 1
                            fd.close()

    def get_user(self):
        user_list = []
        if os.getenv('USER'):
            user_list.append(os.getenv('USER'))
        for user_name in user_list:
            f = open("/etc/passwd", 'r')
            while 1:
                line = f.readline()
                if line:
                    line = line.split(':')
                    if user_name == line[0]:
                        break
                if not line:
                    f.close()
                    return
            f.close()
            self.user.append(user_name)
            self.user.append(line[4])

def check_makefile(thedir):
    file = thedir + "Makefile"
    if os.path.isfile(file):
        try:
            fd = open(file, 'r')
        except IOError:
            print "Impossible d'ouvrir le Makefile"
        else:
            buffer = fd.read()
            p = re.compile('(-g|-pg|-lefence)')
            test = re.search(p, buffer)
            if test:
                print "Options de debug dans le Makefile"
            p = re.compile('(-Wall)')
            test = re.search(p, buffer)
            if not test:
                print "-Wall n'est pas dans le Makefile"
            p = re.compile('(-pedantic)')
            test = re.search(p, buffer)
            if not test:
                print "-pedantic n'est pas dans le Makefile"
            if buffer[:2] != "##":
                print "Header du Makefile invalide"
            fd.close()

def get_files(argv):
    li = []
    pattern = re.compile('[.]c$|[.]h$')
    for arg in sys.argv:
        test = re.search(pattern, arg)
        if test:
            li.append(arg)
    return li

def is_indent_key(line):
    p = re.compile('^([ \t]+)(if|else|while)+(.*)')
    test = re.search(p, line)
    if test:
        if (line[-2:-1] != ';'):
            return True
    return False

def is_open_brace(line):
    p = re.compile('([ ]|[\t])*({)')
    test = re.search(p, line)
    if test:
        return True
    return False

def is_close_brace(line):
    p = re.compile('([ ]|[\t])*(})')
    test = re.search(p, line)
    if test:
        return True
    return False

def is_commented(line):
    if ((line[0] == '/' or line[0] == '*') and line[1] == '*'):
        return True
    return False

def check_version():
    print "\033[0;36;40mVérification de la version de la moulinette...\033[0m"
    file = "http://webcomputing.fr/Epitech/version"
    try:
        f = urllib2.urlopen(file)
    except urllib2.HTTPError, e:
        print "Impossible de vérifier la version du script"
        print "Erreur accès :", e.code
    except urllib2.URLError, e:
        print "Impossible de vérifier la version du script"
        print "Erreur URL : ", e.reason
    else:
        buf = f.read(2048)
        if (version == buf):
            print "\033[0;32;40mVotre moulinette est à jour.\nVersion : " + version +"\033[0m"
            return True
        else:
            print "\033[0;31;40mMauvaise version du script.\nTéléchargez la dernière version : \033[0;33;40mperso.eptich.net/~maillo_a/moulinette/\033[0m"
            print "\033[0;31;40mOu \033[0;33;40m./norme_auto -update\033[0m"
            print "\033[0;31;40mVersion possédée : \033[0;33;40m"+ version +"\033[0;31;40m\nVersion actuelle : \033[0;33;40m"+ buf +"\033[0m"
            return False

def help():
    print "\033[0;32;40m\nAide :"
    print "Usage: norme.py <files_to_scan>"
    print "-verbose: affiche les messages impossible d'ouvrir"
    print "-cheat  : active la detection de la triche"
    print "-score  : affiche le nombre de faute de norme"
    print "-libc   : active la vérification des fonctions de la libc"
    print "-printline: affiche la ligne provoquant une erreur"
    print "-return : active vérifier le retour des fonctions (return ;)"
    print "-comment: ne pas vérifier les commentaires\033[0m"
    sys.exit()

def norme_malloc():
    file_malloc = open("norme_malloc.c", "w")
    file_malloc.write("/*\n** norme_malloc.c for norme malloc path\n**\n**")
    file_malloc.write(" Made by maillot\n** Login   <maillo_f@epitech.net>\n**\n")
    import datetime
    file_malloc.write("** Started on  ")
    file_malloc.write(datetime.datetime.now().strftime("%a %b %d %H:%M:%S %Y"));
    file_malloc.write(" maillot\n** Last update")
    file_malloc.write(datetime.datetime.now().strftime(" %a %b %d %H:%M:%S %Y"));
    file_malloc.write(" maillot\n*/\n\n#include\t<string.h>\n\n")
    file_malloc.write("void\t\t*malloc(size_t size)\n{\n  return (NULL);\n}")
    file_malloc.close()
    sys.exit()

def main():
    if '-malloc' in sys.argv[1:]:
        norme_malloc()
    if '-help' in sys.argv[1:]:
        check_version()
        help()
    if '-version' in sys.argv[1:]:
        check_version()
        sys.exit()
    if len(sys.argv) == 1:
        print "Usage: norme.py <files_to_scan>"
    moulin = norme()
    files = get_files(sys.argv)
    if '-verbose' in sys.argv[1:]:
        moulin.verbose = 1
    if '-comment' in sys.argv[1:]:
        moulin.comment = 0
    if '-cheat' in sys.argv[1:]:
        moulin.cheat = 1
    if '-score' in sys.argv[1:]:
        moulin.score = 1
    if '-libc' in sys.argv[1:]:
        moulin.libc = 0
    if '-printline' in sys.argv[1:]:
        moulin.printline = 1
    if '-return' in sys.argv[1:]:
        moulin.creturn = 0
    if moulin.cheat == 1:
        moulin.get_user()
    try:
        moulin.scan_files(files)
    except NameError:
        print "Usage: norme.py <files_to_scan>"
    if moulin.score:
        print "Note:",-moulin.note,

if __name__ == "__main__":
    main()
