##
# mruby-x11-simple rake file
#

MRuby::Gem::Specification.new('mruby-x11-simple') do |spec|

  # General spec
  spec.license = 'MIT'
  spec.author  = 'dyama'
  spec.summary = 'Simple X11 windows.'

  spec.cxx.flags << "/I/usr/include"
  spec.linker.libraries << ['X11']

end

