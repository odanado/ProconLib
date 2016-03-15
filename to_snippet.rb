#!/usr/bin/env ruby

def write_snippet(snippet_file_name, snippet_name, snippet)
    file = File.open("#{Dir.home}/dotfiles/.vim/snippets/cpp/" + snippet_file_name, 'w')
    file.write('snippet ' + snippet_name + "\n")
    file.write(snippet)
end

def read_snippet(file_name)
    snippet = ""
    file = File.open(file_name)
    file.each{|line|
        snippet += "\t" + line
    }
    snippet
end

def cnv(file_name)
    snippet_name = file_name.scan(/^.*\/(\w+)\.cpp/).first.first
    snippet_file_name = file_name.gsub('cpp', 'snip')
    snippet = read_snippet(file_name)

    write_snippet(snippet_file_name, snippet_name, snippet)
end

ARGV.each{|file_name|
    cnv(file_name)
}
