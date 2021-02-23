cmd_/work/Module.symvers := sed 's/ko$$/o/' /work/modules.order | scripts/mod/modpost  -a   -o /work/Module.symvers -e -i Module.symvers  -N -T -
