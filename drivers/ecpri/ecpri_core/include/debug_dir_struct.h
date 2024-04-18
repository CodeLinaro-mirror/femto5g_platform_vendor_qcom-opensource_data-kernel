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
							,fh0:misc \
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
							,fh0:ingress_config \
							,fh0:egress_ipv4_cfg \
							,fh0:egress_ipv6_cfg \
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
							,fh1:misc \
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
							,fh1:ingress_config \
							,fh1:egress_ipv4_cfg \
							,fh1:egress_ipv6_cfg \
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
							,fh2:misc \
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
							,fh2:ingress_config \
							,fh2:egress_ipv4_cfg \
							,fh2:egress_ipv6_cfg \
						} \
					} \
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
