require 'open3'

describe "Ruby impelementation" do
  it "can print numbers" do
    program = "puts 1 + 3"
    output = run(program)
    expect(output).to eq("4")
  end

  it "can handle order of operations" do
    program = "puts 1 + 3 * 2 - 1"
    output = run(program)
    expect(output).to eq("6")
  end

  it "can handle multiple lines" do
    program =<<-RUBY
    puts 1 + 3
    puts 4 * 2
    RUBY

    output = run(program)
    expect(output).to eq("4\n8")
  end

  it "can handle parenthesis" do
    program = "puts (1 + 3) * (2 - 1)"
    output = run(program)
    expect(output).to eq("4")
  end

  def run(program)
    stdout,_,_ = Open3.capture3("./ruby", stdin_data: program)
    stdout.chomp
  end
end
