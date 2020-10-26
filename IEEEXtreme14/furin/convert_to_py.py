# Taken from https://codereview.stackexchange.com/questions/196406/brainfuck-to-python-compiler
import itertools
from textwrap import dedent
from contextlib import suppress


BYTECODES = {
        '+': '{0: >{1}}add(data, index, {2})',
        '-': '{0: >{1}}sub(data, index, {2})',
        '<': '{0: >{1}}index -= {2}',
        '>': '{0: >{1}}index += {2}',
        '.': '{0: >{1}}putchar(data, index, {2})',
        ',': '{0: >{1}}getchar(data, index, {2})',
}


def pairwise(iterable):
    a, b = itertools.tee(iterable)
    next(b, None)
    yield from itertools.zip_longest(a, b)


def compile(sourcecode):
    yield dedent("""\
            from collections import defaultdict
            from msvcrt import getch


            def add(data, index, x):
                data[index] = (data[index] + x) % 256


            def sub(data, index, x):
                data[index] = (data[index] - x) % 256


            def putchar(data, index, x):
                for _ in range(x):
                    print(chr(data[index]), end='')


            def getchar(data, index, x):
                for _ in range(x):
                    data[index] = getch()[0]


            def main():
                index = 0
                data = defaultdict(int)""")

    level = count = 1
    for operation, next_operation in pairwise(sourcecode):
        if operation == '[':
            yield f'{"": >{level*4}}while data[index]:'
            level += 1
        elif operation == ']':
            level -= 1
            if level < 1:
                raise ValueError('Unbalanced brackets, found ] before opening [')
        elif operation == next_operation:
            count += 1
        else:
            with suppress(KeyError):
                yield BYTECODES[operation].format('', level * 4, count)
            count = 1

    yield dedent("""\


            if __name__ == '__main__':
                main()""")


def translate(sourcecode):
    return '\n'.join(compile(sourcecode))


if __name__ == '__main__':
    code = """
                                     >,<>>,>,<[->-               
                                  >+<><<]+->>[-<<+>>]            
                                <+-><><<<[-+->-<+-<+>]<          
                               [->+<]><>>>>>><>++->>+->>         
                              >>>+[>><>>>[-]<[-<>-+]<<>[-        
                             +-]-++-+-<         [-]<><<>[+       
                            ---+]<><<             <<+-<<<<>      
                           -+<><<<>                 <+-<<[->     
                          >>>>>>+                     >>>>>-+    
                         >+<<<><            <          <><<<<<   
                        <<<<]>[           ->>           >>><><>  
                       ><>>+>>          >>>>+            <<<<<>< 
                      <<<<+-<           <<<]>             [->>>>>
                                        >><>+                    
                                        >>>>-                    
                                        +><>>                    
                                        +<<<<                    
                                        <<+-<                    
         <<<><<<<        -+><]     >>-++-+>+-+[<-]      <[->>    
      <>++-<<<]>>>>      [-<<<     +--+<<<<+>><>>>      >>>]>    
     [-<<-+<<<<<+<>>     +->>>     >>>]>[-<<<<><<<      ><<+>    
    >>>>>>]>>>>>><>>+    [-<<<     <+--+<><+-<<<<<      <[->>    
   +>>+<<<<]+->[->>+>>   +-+<<     <<]>[-<<+>>]>[-      <<+>>    
  ]+[[<>-]-++>[<-]<+-[   +--><     >><>-<<<]>>-+->      >>+>[    
 <-]<+-[-       >+>[-    <-]<[          >>[-<           <-+->    
 ]-<<[->         ><-     >+->-          +-<<<           <]]<]    
 >>-<<<           <      <+>[>          <<-]<           [>+->    
[-+<<-                   >]<<[          <]]>-           +-]>>    
>>><>>                   >><>+          ]-<<<           >+-<<    
<>+>-                    ++[<-          ]<[-+           >>+[<    
<<>->                    -+]<<          [>>>+           [<-+<    
<->>]                    <<<[<          ]]]>-           ]>>>>    
[-]<<                    <<<<<          -+<><           <<<<<    
<[-]>                    >+>+[          <-]<[           ->>+<    
><<<]                    >+>[<          -]<[>           >[<<-    
>]<<[                    <]]>-          [+>>>           >>>><    
++-++                    +++++          ++<<<           <<<+>    
+-[<<>                   -]<[>          >[<<-           >]<<[    
<]]>-[                   ++>[<          -]<[-           >>-<<    
 <]>>->           >      +>>+>          -[<-]           <[<<[    
 ->>>+<<         ><<     ]+->>          >>>+>           +[<><    
 -]<><[->       >+<<<    ]<<-<          ]<<<<           +>[<-    
  ]<[>>[<<->]<<[<]]>-]   >>+++          +++++[   ->     +++++    
   +<]>[-<<<<+>>>>]>>>   >>+><          >-+[<-]<[>>     [<<->    
    ]<<[<]]>-[++>[<-]    <[->>          -<<<]>>-<<<     <<<<<    
     +>+[<-]<[->>+<<     <]>>>          >>>>>+>[<-      ]<[>>    
      [<<->]<<[<]]>      -]<<[           -]<<<<<+>      [<-]<    
         [>>[<<->        ]<<[<            ]]>-]<<       [.<]!    
""".replace(" \t\n", "")
    for line in compile(code):
        print(line)

    print('*------*')
    with open("code.py", "w") as f:
        f.write(translate(code))
