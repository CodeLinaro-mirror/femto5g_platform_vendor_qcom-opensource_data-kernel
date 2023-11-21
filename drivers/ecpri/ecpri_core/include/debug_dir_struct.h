#ifndef NO_DEBUGFS_PERF
#define TREE "\
{ \
	ecpri_ss \
	{ \
		stats \
		{ \
			qudp \
			{\
				fh  \
				{ \
					fh_0  \
					{ \
						link_0  \
						{ \
							,fh:stats:00  \
							,fh:interrupts:00  \
						} \
						link_1  \
						{ \
							,fh:stats:01  \
							,fh:interrupts:01  \
						} \
						link_2  \
						{ \
							,fh:stats:02  \
							,fh:interrupts:02  \
						} \
						link_3  \
						{ \
							,fh:stats:03  \
							,fh:interrupts:03  \
						} \
					} \
					fh_1  \
					{ \
						link_0  \
						{ \
							,fh:stats:10  \
							,fh:interrupts:10  \
						} \
						link_1  \
						{ \
							,fh:stats:11  \
							,fh:interrupts:11  \
						} \
						link_2  \
						{ \
							,fh:stats:12  \
							,fh:interrupts:12  \
						} \
						link_3  \
						{ \
							,fh:stats:13  \
							,fh:interrupts:13  \
						} \
					} \
					fh_2  \
					{ \
						link_0  \
						{ \
							,fh:stats:20  \
							,fh:interrupts:20  \
						} \
						link_1  \
						{ \
							,fh:stats:21  \
							,fh:interrupts:21  \
						} \
						link_2  \
						{ \
							,fh:stats:22  \
							,fh:interrupts:22  \
						} \
						link_3  \
						{ \
							,fh:stats:23  \
							,fh:interrupts:23  \
						} \
					} \
				} \
				c2c  \
				{ \
					c2c_0  \
					{ \
						link_0  \
						{ \
							,c2c:stats:00  \
							,c2c:interrupts:00  \
						} \
						link_1  \
						{ \
							,c2c:stats:01  \
							,c2c:interrupts:01  \
						} \
						link_2  \
						{ \
							,c2c:stats:02  \
							,c2c:interrupts:02  \
						} \
						link_3  \
						{ \
							,c2c:stats:03  \
							,c2c:interrupts:03  \
						} \
					} \
					c2c_1  \
					{ \
						link_0  \
						{ \
							,c2c:stats:10  \
							,c2c:interrupts:10  \
						} \
						link_1  \
						{ \
							,c2c:stats:11  \
							,c2c:interrupts:11  \
						} \
						link_2  \
						{ \
							,c2c:stats:12  \
							,c2c:interrupts:12\
						} \
						link_3  \
						{ \
							,c2c:stats:13  \
							,c2c:interrupts:13  \
						} \
					} \
					c2c_2  \
					{ \
						link_0  \
						{ \
							,c2c:stats:20  \
							,c2c:interrupts:20  \
						} \
						link_1  \
						{ \
							,c2c:stats:21  \
							,c2c:interrupts:21  \
						} \
						link_2  \
						{ \
							,c2c:stats:22  \
							,c2c:interrupts:22  \
						} \
						link_3  \
						{ \
							,c2c:stats:23  \
							,c2c:interrupts:23  \
						} \
					} \
				} \
				l2 \
				{ \
					,dummy \
				} \
			} \
			xbar \
			{\
				,xb:stats \
				,xb:interrupts \
			}\
		} \
		config \
		{ \
			qudp \
			{\
				fh  \
				{ \
					fh_0  \
					{ \
						egress \
						{\
							,fh0:udp_ports  \
							,fh0:src_ip_addr \
							,fh0:dst_ip_addr \
							,fh0:vlan_ethertype \
							,fh0:eth_src0 \
							,fh0:eth_src1 \
							,fh0:eth_dst0 \
						} \
						ingress \
						{\
							filter \
							{ \
								,fh0:vlan_fltr \
								,fh0:udp_classification \
								,fh0:ip_dts_fltr \
								,fh0:mac	\
								,fh0:valid_bits	\
							} \
						} \
						global \
						{\
							,fh0:config \
						} \
					} \
					fh_1  \
					{ \
						egress \
						{\
							,fh1:udp_ports  \
							,fh1:src_ip_addr \
							,fh1:dst_ip_addr \
							,fh1:vlan_ethertype \
							,fh1:eth_src0 \
							,fh1:eth_src1 \
							,fh1:eth_dst0 \
						} \
						ingress \
						{\
							filter \
							{ \
								,fh1:vlan_fltr \
								,fh1:udp_classification \
								,fh1:ip_dts_fltr \
								,fh1:mac	\
								,fh1:valid_bits	\
							} \
						} \
						global \
						{\
							,fh1:config \
						} \
					} \
					fh_2  \
					{ \
						egress \
						{\
							,fh2:udp_ports  \
							,fh2:src_ip_addr \
							,fh2:dst_ip_addr \
							,fh2:vlan_ethertype \
							,fh2:eth_src0 \
							,fh2:eth_src1 \
							,fh2:eth_dst0 \
						} \
						ingress \
						{\
							filter \
							{ \
								,fh2:vlan_fltr \
								,fh2:udp_classification \
								,fh2:ip_dts_fltr \
								,fh2:mac	\
								,fh2:valid_bits	\
							} \
						} \
						global \
						{\
							,fh2:config \
						} \
					} \
				} \
				c2c  \
				{ \
					,dummy \
				} \
				l2 \
				{ \
					,dummy \
				} \
			} \
			xbar \
			{ \
				lut \
				{\
					ocrx \
					{\
						,fh0:ocrx_fh0\
						,fh1:ocrx_fh1\
						,fh2:ocrx_fh2\
					} \
					fhrx \
					{\
						,fh0:fhrx_fh0\
						,fh1:fhrx_fh1\
						,fh2:fhrx_fh2\
					} \
					c2crxDL \
					{\
						,fh0:c2crxDL_fh0\
						,fh1:c2crxDL_fh1\
						,fh2:c2crxDL_fh2\
					} \
					c2crxUL \
					{\
						,fh0:c2crxUL_fh0\
						,fh1:c2crxUL_fh1\
						,fh2:c2crxUL_fh2\
					} \
				} \
				global \
				{ \
					,xbar:global_config \
				} \
			} \
			gcfg \
			{ \
				 ecpriss_strict_filt_config \
				{\
					,fh0:qudp_strict_filt_cfg_fh0 \
					,fh1:qudp_strict_filt_cfg_fh1 \
					,fh2:qudp_strict_filt_cfg_fh2 \
				} \
				,ecpriss_filt \
				,ecpriss_stats_timeout \
				,ecpriss_clear_stats \
				,ecpriss_config_qudp_ingress_action \
			} \
		} \
	} \
} \
"
#endif
