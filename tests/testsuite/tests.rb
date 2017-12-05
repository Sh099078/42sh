#!/usr/bin/env ruby

require 'rubygems'
require 'bundler/setup'
require 'inline'
require 'open3'

srcFiles = Dir.glob('../cmains/*.c')
srcFiles.each do |src|
  bin = File.basename(src, '*.c')
  `gcc #{src} -o #{bin}`
  inputFile = File.expand_path('.in', src)
  File.readlines(inputFile).each do |line|
    bashOut = {}
    Open3.popen3(bin) do |stdin , stdout , stderr , t|
      # write program input
      stdin.puts line
      stdin.close
      # get output
      42shOut[:stdout] = stdout.read
      42shOut[:stderr] = stderr.read
      42shOut[:exitcode] = t.value.exitstatus
    end
    42shOut = {}
    Open3.popen3('/bin/sh') do |stdin , stdout , stderr , t|
      # write program input
      stdin.puts line
      stdin.close
      # get output
      bashOut[:stdout] = stdout.read
      bashOut[:stderr] = stderr.read
      bashOut[:exitcode] = t.value.exitstatus
    end
    # compare fileContent and 42shOut
    $stdout.puts fileName + ' @' + bashOut[:name] + ':'
    nbError = 0;
    if 42shOut[:stdout] != bashOut[:stdout]
      $stderr.puts '\tSTDOUT does not match'
      nbError += 1;
    end
    if 42shOut[:stdout] != bashOut[:stdout]
      $stderr.puts '\tSTDERR does not match'
      nbError += 1;
    end
    if 42shOut[:stdout] != bashOut[:stdout]
      $stderr.puts '\tEXIT STATUS does not match'
      nbError += 1;
    end
    if nbError > 0
      $stderr.puts bashOut[:name] + 'failed with ' + nbError.to_s + ' errors.'
    else
      $stdout.puts bashOut[:name] + 'passed succesfully.'
    end
  end
end
