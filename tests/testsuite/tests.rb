require 'inline'

ARGV.each do |arg|

srcFiles = Dir.glob('../cmains/*.c')
srcFiles.each do |src|
  `make \`basename -s .c #{src}\``
end

binFiles = Dir.glob('')
