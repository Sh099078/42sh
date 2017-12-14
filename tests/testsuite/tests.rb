#!/usr/bin/env ruby

require 'rubygems'
require 'bundler/setup'
require 'open3'
require 'json'
require 'colorize'

=begin
  *
=end

jsonFiles = Dir.glob('**/*.json')
nbError = 0;
jsonFiles.each do |file|
  parsedJson = JSON.parse(file)
  testName = parsedJson['name']
  testArray = parsedJson['tests']
  # Each JSON file contains an array of name-input hashmaps
  testArray.each do |hash|
    mybashOut = {}
    bashOut = {}
    # Execute my 42sh renamed as bash
    Open3.popen3('./bash') do |stdin , stdout , stderr , t|
      # write program input
      stdin.puts hash['input']
      stdin.close
      # get output
      mybashOut[:stdout] = stdout.read
      mybashOut[:stderr] = stderr.read
      mybashOut[:exitcode] = t.value.exitstatus
    end
    # Execute real bash
    Open3.popen3('./bin/bash') do |stdin , stdout , stderr , t|
      # write program input
      stdin.puts hash['input']
      stdin.close
      # get output
      bashOut[:stdout] = stdout.read
      bashOut[:stderr] = stderr.read
      bashOut[:exitcode] = t.value.exitstatus
    end
    # compare outputs from bash and 42sh
    testNbError = nbError
    $stdout.puts "\t #{hash['name']}"
    if mybashOut[:stdout] != bashOut[:stdout]
      $stderr.puts '\tSTDOUT does not match'.colorize(:red)
      nbError += 1;
    end
    if mybashOut[:stderr] != bashOut[:stderr]
      $stderr.puts '\tSTDERR does not match'.colorize(:red)
      nbError += 1;
    end
    if mybashOut[:exitcode] != bashOut[:exitcode]
      $stderr.puts '\tEXIT STATUS does not match'.colorize(:red)
      nbError += 1;
    end
    if nbError != testNbError
      $stderr.puts "#{hash['name']} failed with #{nbError - testNbError} errors.".colorize(:red)
    else
      $stdout.puts "#{bashOut['name']} passed succesfully."
    end
  end
  if nbError > 0
    $stdout.puts "${parsedJson['name']} "
end
