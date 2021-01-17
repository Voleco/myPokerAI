#-----------------------------------------------------------------------------
# GNU Makefile: part for executables
#
#-----------------------------------------------------------------------------

$(DBG_BINDIR)/$(DBG_NAME): $(DBG_OBJS) $(PROJ_DBG_DEP)
	@echo "Linking $@"
	mkdir -p $(dir $@)
	$(LN) -o $@ $(DBG_OBJS) $(PROJ_DBG_LIB) $(DBG_LNFLAGS)

$(REL_BINDIR)/$(REL_NAME): $(REL_OBJS) $(PROJ_REL_DEP)
	@echo "Linking $@"
	mkdir -p $(REL_BINDIR)
	$(LN) -o $@ $(REL_OBJS) $(PROJ_REL_LIB) $(REL_LNFLAGS)
