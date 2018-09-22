import os

def line_count(file_name):
  with open(file_name) as fil:
    num_lines = 0
    for line in fil:
      num_lines += 1
    return num_lines

def word_count(file_name):
  with open(file_name) as fil:
    num_words = 0
    for line in fil:
      words = line.split()
      num_words += len(words)
      #for word in words:
      #  num_words += 1
    return num_words

if __name__ == '__main__':
  os.chdir('..')
  #print(os.listdir())
  cd = os.getcwd()
  print(cd)
  junk = os.path.join(cd, 'Files', 'junk.txt')
  junk2 = 'Files'+os.path.sep +'junk.txt'
  print(junk)
  print(junk2)
  print(line_count(junk))
  print(line_count(junk2))
