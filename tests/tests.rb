#!/usr/bin/env ruby

require 'rubygems'
require 'bundler/setup'
require 'open3'
require 'json'
require 'colorize'

jsonFiles = Dir.glob('inputs/*.json')
nbError = 0;
jsonFiles.each do |file|
  content = File.read(file)
  parsedJson = JSON.parse(content)
  testName = parsedJson['name']
  testArray = parsedJson['tests']
  $stdout.puts "\#\#\#\#\#   #{testName}   \#\#\#\#\#\n"
  # Each JSON file contains an array of name-input hashmaps
  testArray.each do |hash|
    mybashOut = {}
    bashOut = {}
    # Execute my 42sh renamed as bash
    Open3.popen3("bash") do |stdin , stdout , stderr , t|
      # write program input
      stdin.puts hash['input']
      stdin.close
      # get output
      mybashOut[:stdout] = stdout.read
      mybashOut[:stderr] = stderr.read
      mybashOut[:exitcode] = t.value.exitstatus
    end
    # Execute real bash
    Open3.popen3("/bin/bash") do |stdin , stdout , stderr , t|
      # write program input
      stdin.puts hash['input']
      stdin.close
      # get output
      bashOut[:stdout] = stdout.read
      bashOut[:stderr] = stderr.read
      if bashOut[:stderr] != ""
        bashOut[:stderr] = bashOut[:stderr][5..-1]
      end
      bashOut[:exitcode] = t.value.exitstatus
    end
    # compare outputs from bash and 42sh
    testNbError = nbError
    $stdout.puts "\n\t\#\#\#   #{hash['name']}   \#\#\#"
    if mybashOut[:stdout] != bashOut[:stdout]
      $stderr.puts "STDOUT does not match".colorize(:light_red)
      $stderr.puts "expected:\n#{bashOut[:stdout]}\n42sh:\n#{mybashOut[:stdout]}"
      nbError += 1;
    end
    if mybashOut[:stderr] != bashOut[:stderr]
      $stderr.puts "STDERR does not match".colorize(:light_red)
      $stderr.puts "expected:\n#{bashOut[:stderr]}\n42sh:\n#{mybashOut[:stderr]}"
      nbError += 1;
    end
    if mybashOut[:exitcode] != bashOut[:exitcode]
      $stderr.puts "EXIT STATUS does not match".colorize(:light_red)
      $stderr.puts "expected:\n#{bashOut[:exitcode]}\n42sh:\n#{mybashOut[:exitcode]}"
      nbError += 1;
    end
    puts mybashOut
    puts bashOut
    if nbError != testNbError
      $stderr.puts "\n#{hash[:name]} failed with #{nbError - testNbError} errors.".colorize(:light_red)
    else
      $stdout.puts "\n#{hash[:name]} passed succesfully.".colorize(:light_green)
    end
  end
  if nbError > 0
    $stderr.puts "\n#{parsedJson[:name]} tests finished with #{nbError} errors".colorize(:red)
  else
    $stdout.puts "\n#{parsedJson[:name]} tests finished succesfully".colorize(:light_green)
  end
end
