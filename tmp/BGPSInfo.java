package com.xunzhi.busgebus.model;

import java.math.BigDecimal;
import java.util.Date;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.SequenceGenerator;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

import org.hibernate.annotations.Fetch;
import org.hibernate.annotations.FetchMode;

/**
 * 车辆信息表
 * @author xuqq   2015年6月4日    下午3:07:52
 *
 */
@Entity
@Table(name = "B_GPS_INFO", schema = "YOUTU")
public class BGPSInfo implements java.io.Serializable {
					
						
	/**
	 * GPS Device ID
	 */
	private String deviceId;
	/**
	 * 经度
	 */
	private BigDecimal latitude;
	/**
	 * 纬度
	 */
	private BigDecimal longitude;
	/**
	 * 航向	
	 */
	private BigDecimal heading;
	/**
	 * 速度
	 */
	private BigDecimal speed;
	/**
	 * 经度标识
	 */
	private BigDecimal latiType;
	/**
	 * 纬度标识
	 */
	private Date longiType;
	/**
	 * GPS时间
	 */
	private Date gpsTime;
	
	@Column(name = "DEVICE_ID", nullable = false, length = 8)
	public String getDeviceId() {
		return this.deviceId;
	}

	public void getDeviceId(String deviceId) {
		this.deviceId = deviceId;
	}

	@Column(name = "LATITUDE", precision=12, scale= 5)
	public BigDecimal getLatitude() {
		return this.latitude;
	}

	public void setLatitude(BigDecimal latitude) {
		this.latitude = latitude;
	}

	@Column(name = "LONGITUDE", precision=12, scale= 5)
	public BigDecimal getLongitude() {
		return this.longitude;
	}

	public void setLongitude(BigDecimal longitude) {
		this.longitude = longitude;
	}

	@Column(name = "HEADING", precision=5, scale= 0)
	public BigDecimal getHeading() {
		return this.heading;
	}

	public void setHeading(BigDecimal heading) {
		this.heading = heading;
	}
	

	@Temporal(TemporalType.TIMESTAMP)
	@Column(name = "CREATE_TIME", length = 7)
	public Date getCreateTime() {
		return this.createTime;
	}

	public void setCreateTime(Date createTime) {
		this.createTime = createTime;
	}

	@Column(name = "CREATE_USER_ID", precision = 22, scale = 0)
	public BigDecimal getCreateUserId() {
		return this.createUserId;
	}

	public void setCreateUserId(BigDecimal createUserId) {
		this.createUserId = createUserId;
	}

	@Temporal(TemporalType.TIMESTAMP)
	@Column(name = "UPDATE_TIME", length = 7)
	public Date getUpdateTime() {
		return this.updateTime;
	}

	public void setUpdateTime(Date updateTime) {
		this.updateTime = updateTime;
	}

	@Column(name = "UPDATE_USER_ID", precision = 22, scale = 0)
	public BigDecimal getUpdateUserId() {
		return this.updateUserId;
	}

	public void setUpdateUserId(BigDecimal updateUserId) {
		this.updateUserId = updateUserId;
	}

	@Column(name = "LOCATION_TYPE", precision = 22, scale = 0)
	public BigDecimal getLocationType() {
		return locationType;
	}

	public void setLocationType(BigDecimal locationType) {
		this.locationType = locationType;
	}
	
	@Column(name = "ROUTE_ID", precision = 22, scale = 0)
	public BigDecimal getRouteId() {
		return routeId;
	}

	public void setRouteId(BigDecimal routeId) {
		this.routeId = routeId;
	}


	@Column(name = "REGION_ID", precision = 22, scale = 0)
	public BigDecimal getRegionId() {
		return regionId;
	}

	public void setRegionId(BigDecimal regionId) {
		this.regionId = regionId;
	}

	@Column(name = "ORDER_NUMBER", precision = 22, scale = 0)
	public BigDecimal getOrderNumber() {
		return orderNumber;
	}

	public void setOrderNumber(BigDecimal orderNumber) {
		this.orderNumber = orderNumber;
	}
	@ManyToOne(fetch=FetchType.LAZY)
	@JoinColumn(name="ROUTE_ID",insertable=false,updatable=false)
	@Fetch(FetchMode.SELECT)
	public BRoute getRoute() {
		return route;
	}

	public void setRoute(BRoute route) {
		this.route = route;
	}

	@Column(name = "LOCATION_STATUS", precision = 22, scale = 0)
	public BigDecimal getLocationStatus() {
		return locationStatus;
	}

	public void setLocationStatus(BigDecimal locationStatus) {
		this.locationStatus = locationStatus;
	}

	@Column(name = "HOT_INDEX", precision = 22, scale = 0)
	public BigDecimal getHotIndex() {
		return hotIndex;
	}

	public void setHotIndex(BigDecimal hotIndex) {
		this.hotIndex = hotIndex;
	}
	
	@Column(name = "LOCATION_DESCRIPTION",  length = 100)
	public String getLocationDescription() {
		return locationDescription;
	}

	public void setLocationDescription(String locationDescription) {
		this.locationDescription = locationDescription;
	}

	
	
	
}