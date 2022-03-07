def statusHVreturn
  @vmeEasiroc.sendMadcControl

  ## Read the MPPC bias voltage & return
  return rd_madc = @vmeEasiroc.readMadc(3)
  #puts sprintf("Bias voltage >> %.2f V", rd_madc)

end
