#!/usr/bin/env ruby

# Generate some colour mappings
range = (0..255).step(70)

File.open("colours.txt", 'w+') do |file|
  range.each do |r|
    range.each do |g|
      range.each do |b|
        file.puts "{ #{r}, #{g}, #{b} },"
      end
    end
  end
end
