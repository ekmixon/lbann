import sys

if len(sys.argv) != 3:
  print('usage:')
  print(f'  {sys.argv[0]} input_fn output_fn')
  print('function:')
  print('  writes data for plotting num_sequences as a function')
  print('  of sequence length to "output_fn"; prints length')
  print('  of longest sequence to cout (add two for <bos>, <eos>)')
  print('delimiter:')
  print('  is hard-coded for comma\n')
  exit(9)

a = open(sys.argv[1])
a.readline() #discard header
with open(sys.argv[2], 'w') as out:
  longest = 0
  longest_seq = ''
  longest_line_num = 0

  data = {}
  for j, line in enumerate(a, start=1):
    if j % 1000 == 0:
      print(f'{str(j/1000)}K lines processed')
    t = line.split(',')
    x = len(t[0])
    if x not in data :
      data[x] = 0
    data[x] += 1
    if x > longest : 
      longest = x
      longest_seq = t[0]
      longest_line_num = j-1

  v = sorted(data.items())
  for d in v:
    out.write(f'{str(d[0])} {str(d[1])}' + '\n')
  print('\noutput written to: ', sys.argv[2] + '\n')
print('\nlongest sequence length: ' + str(longest))
print(f'line number of longest: {str(longest_line_num)}')
print(f'longest sequence length: {longest_seq}')
