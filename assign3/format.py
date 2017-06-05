#! /usr/bin/python
import fileinput
import sys

# Global opts
opts = { 
    '.FT'     : False,      # Is formatting on or off?
    '.LW'  : 0,          # The Maximum width of any given line. May change throughout processing.
    '.LM'    : 0,          # Desired page margin. Cannot be less then or equal to pgwdth-20
}

state = {
    'line_size' : 0,
    'last_was_new' : False
}

def main ():
    """
    Format according to given control sequences.
    """
    # Define our variables.
    # The currently calculated output.
    output = ""

    # Process each line. If we detect a control sequence on the line, return none. If we detect [], add an extra newline. Otherwise just check for paragraph size and margin. The output will be joined with 'output'
    lines =  [ line for line in fileinput.input() ]
    processed = [ process(line) for line in lines]
    no_empty = [ line for line in processed if line != None ]
    
    if len(no_empty) == 0:
        return
    else:
        output = "".join(no_empty)
        print output,
    
def process (line):
    """ 
    Process the line. Check for control sequences, set any flags required. Format appropriately.
    """
    global opts, state

    split = line.split()
    # Detect control sequences.
    if len(split) is not 0:
        if split[0] == ".FT":
            if split[1] == "off":
                opts['.FT'] = False
            elif split[1] == "on":
                opts['.FT'] = True
            return None
        elif split[0] == ".LW": # Also turns on fmt
            if isinstance(int(split[1]), int):
                opts['.LW'] = int(split[1])
                opts['.FT'] = True
            elif split[1][0] == '-':
                opts['.LW'] -= int(split[1][1:])
                opts['.FT'] = True
            elif split[1][0] == '+':
                opts['.LW'] += int(split[1][1:])
                opts['.FT'] = True
            return None
        elif split[0] == ".LM":
            if split[1][:1] == "-":
                opts['.LM'] -= int(split[1][1:])
                if opts['.LM'] < 0:
                    opts['.LM'] = 0
            elif split[1][:1] == "+":
                opts['.LM'] += int(split[1][1:])
            else:
                opts['.LM'] = int(split[1])
            # Restriction on margins.
            if opts['.LM'] > opts['.LW'] - 20:
                opts['.LM'] = opts['.LW'] - 20
            return None
            
    # Output the line
    if opts['.FT']:
        # Special case for empty lines.
        if split == []:
            state['line_size'] = 0
            if state['last_was_new']:
                return '\n'
            else:
                state['last_was_new'] = True
                return '\n\n'
        state['last_was_new'] = False
        
        # Do we need a margin? (Is this a new line?)
        if state['line_size'] == 0:
            out = "".join( [" " for i in range(opts['.LM']) ] )
            state['line_size'] = opts['.LM']
        else:
            out = ""
            
        # Gradually add each word, making sure we're not going over the pgwdth
        for word in split:
            # Do we need a new line?
            if state['line_size'] + len(word) >= opts['.LW']:
                margin = "".join( [" " for i in range(opts['.LM']) ] )
                out = out + '\n' + margin
                state['line_size'] = opts['.LM']
            # Otherwise, add a space
            elif state['line_size'] != opts['.LM']:
                state['line_size'] += 1
                out = out + ' '
            # Concatenate
            out = out + word
            state['line_size'] += len(word)
        return out
    else:
        return line
    
# Detect if we're running via ./ or if we're called.
if __name__ == "__main__":
    main()