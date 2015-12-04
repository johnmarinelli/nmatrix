require 'spec_helper'

describe 'issue 411' do
  it "returns true for a positive definite matrix" do 
    n = NMatrix.new([2,2], [0,1,2,3], dtype: :int64)
    expect(n.positive_definite?).to eq(true)
  end
end
