#
# run with python 2.7
#
import string

a1 = string.letters
a2 = string.digits
a3 = string.punctuation
a4 = a1 + a2 + a3

with open('vocab_universal.txt', 'w') as out:
  id = 0
  for c in a4:
    out.write(f'{c} {str(id)}' + '\n')
    id += 1
  out.write(f'<bos> {str(id)}' + '\n')
  id += 1
  out.write(f'<eos> {id}' + '\n')
  id += 1
  out.write(f'<pad> {id}' + '\n')
  id += 1
  out.write(f'<unk> {id}' + '\n')
  id += 1

print('\nwrote file: vocab_universal.txt\n')
