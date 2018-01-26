<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <%@include file="/WEB-INF/jsp/inc/base.jsp" %>
</head>
<body>
<%@include file="/WEB-INF/jsp/inc/header.jsp" %>
<div class="container-fluid">
    <div class="row-fluid">
        <%@include file="/WEB-INF/jsp/inc/left.jsp" %>

        <div id="content" class="span10">
            <!-- content starts -->
            <div class="row-fluid sortable">
				<div class="box span12">
					<div class="box-header well data-original-title">
						<h2><i class="icon-plus"></i>修改路线</h2>
					</div>
					<div class="box-content">
						<form id="myfrom" class="form-horizontal" action="busgebus/route/editRoute" method="post" enctype="multipart/form-data">
						<input type="hidden"  name="routeId" value="${routeForm.route.routeId }">
						<input type="hidden" name="isSubmit" value="1">
							<fieldset>
							  <div class="control-group">
								<label class="control-label" for="focusedInput">路线名</label>
								<div class="controls">
								    <input class="input-xlarge focused" name="routeName"  maxlength='12' type="text" value="${routeForm.route.routeName }" valitype="require">
								    <span class="help-inline">请输入路线名！</span>
								</div>
							  </div>
							  <div class="control-group">
								<label class="control-label" for="focusedInput">起始地点</label>
								<div class="controls">
								    <input class="input-xlarge focused" name="startAddress" value="${routeForm.route.startAddress }"  type="text" valitype="require">
								    <span class="help-inline">请输入起始地点！</span>
								</div>
							  </div>
							  <div class="control-group">
								<label class="control-label">结束地点</label>
								<div class="controls">
									<input class="input-xlarge focused" name="endAddress" value="${routeForm.route.endAddress }" type="text" valitype="require">
									<span class="help-inline">请输入结束地点！</span>
								</div>
							  </div>
							  <div class="control-group">
								<label class="control-label" for="disabledInput">路线状态</label>
								<div class="controls">
								<select class="input-xlarge focused" name="routeStatus" id="routeStatus"  style="width: 280px;" onchange="checkRouteStatus()">
									<option value="">未选择</option>
									<option value="0" 
									<c:if test="${routeForm.route.routeStatus==0}">
										selected="selected"
									</c:if>
									>未开通</option>
									<option value="1"
									<c:if test="${routeForm.route.routeStatus==1}">
										selected="selected"
									</c:if>
									>已开通</option>
								</select>
								<span style="color: #bd4247" id="routeStatusMsg"></span>
								</div>
							  </div>
							    <div class="control-group">
								<label class="control-label" for="disabledInput">路线状态</label>
								<div class="controls">
								<select class="input-xlarge focused" name="routeType" id="routeType" style="width: 280px;" onchange="checkRouteType()">
									<option value="">未选择</option>
									<option value="1" 
									<c:if test="${routeForm.route.routeType==1}">
										selected="selected"
									</c:if>
									>班车线</option>
									<option value="2"
									<c:if test="${routeForm.route.routeType==2}">
										selected="selected"
									</c:if>
									>旅游线</option>
									<option value="3"
									<c:if test="${routeForm.route.routeType==3}">
										selected="selected"
									</c:if>
									>活动线</option>
									<option value="4"
									<c:if test="${routeForm.route.routeType==4}">
										selected="selected"
									</c:if>
									>企业线</option>
									<option value="5"
									<c:if test="${routeForm.route.routeType==4}">
										selected="selected"
									</c:if>
									>免费线</option>
								</select>
								<span style="color: #bd4247" id="routeStatusMsg"></span>
								</div>
							  </div>
							  <div class="control-group">
								<label class="control-label" for="disabledInput">票价</label>
								<div class="controls">
								<input class="input-xlarge focused"  name="ticketPrice" id="ticketPrice" type="text" value="${routeForm.route.ticketPrice }" onchange="checkTicketPrice()">元
								 <span style="color: #bd4247" id="ticketPriceMsg"></span>
								</div>
							  </div>
							  <div class="control-group">
								<label class="control-label" for="disabledInput">原始票价</label>
								<div class="controls">
								<input class="input-xlarge focused"  name="oldPrice" id="oldPrice" type="text" value="${routeForm.route.oldPrice }"  onchange="checkoldPrice()">元
								 <span style="color: #bd4247" id="oldPriceMsg"></span>
								</div>
							  </div>
							  <div class="control-group">
								<label class="control-label" for="disabledInput" >大约时间</label>
								<div class="controls">
								<input class="input-xlarge focused"  name="aboutTime"  id="aboutTime" value="${routeForm.route.aboutTime }" type="text" onchange="checkAboutTime()">分钟
								 <span style="color: #bd4247" id="aboutTimeMsg"></span>
								</div>
							  </div>
							  <div class="control-group">
								<label class="control-label" for="disabledInput" >变更提醒</label>
								<div class="controls">
								<input class="input-xlarge focused"  name="changeRemind" value="${routeForm.route.changeRemind }" type="text">
								</div>
							  </div>
							  <div class="control-group">
								<label class="control-label" for="disabledInput" >提醒结束时间</label>
								<div class="controls">
								<input class="input-xlarge focused"  type="text" onclick="laydate({istime: false, format: 'YYYY-MM-DD'})" name="endRemindTime"  value="${routeForm.route.endRemindTime}">
								</div>
							  </div>
							  <div class="control-group">
								<label class="control-label" for="disabledInput">大约距离</label>
								<div class="controls">
								<input class="input-xlarge focused"  name="aboutDistance" id="aboutDistance" value="${routeForm.route.aboutDistance }" type="text" onchange="checkAboutDistance()">公里
								 <span style="color: #bd4247" id="aboutDistanceMsg"></span>
								</div>
							  </div>
							  <div class="control-group">
								<label class="control-label" for="disabledInput">所在城市</label>
								<div class="controls">
									<select name="regionId" class="input-xlarge focused" >
	                         		<c:forEach var="item" items="${regions}">
	                         			<option value="${item.regionId}" 
	                         				<c:if test="${item.regionId == routeForm.route.regionId}">selected="selected"</c:if>
	                         			>${item.regionName}</option>
	                         		</c:forEach>
	                         		</select>
								</div>
								</div>
							  <div class="control-group">
								<label class="control-label" for="focusedInput">集合标识</label>
								<div class="controls">
								    <input class="input-xlarge focused" name="routeName"  maxlength='12' type="text" value="${routeForm.route.routeAggregateSign }">
								    <span class="help-inline">请输入路线名！</span>
								</div>
							  </div>								
								<div class="control-group">
									<label class="control-label" for="disabledInput">路线背景图片370*124：</label>
									<div class="controls">
										<input type="file" id="file" name="file"/>
										<span class="help-inline">&nbsp;&nbsp;请选择图片&nbsp;&nbsp;</span>
										<span name="file" style="color: red;"></span>
									</div>
								</div>
								<div class="control-group">
									<label class="control-label" for="disabledInput">路线背景原始图片：</label>
									<div class="controls">
										<image src="${routeForm.route.backpic}" style="width:320px;" />
									</div>
								</div>
								<div class="control-group">
									<label class="control-label" for="disabledInput">电子票背景图片491*165：</label>
									<div class="controls">
										<input type="file" id="tfile" name="tfile"/>
										<span class="help-inline">&nbsp;&nbsp;请选择图片&nbsp;&nbsp;</span>
										<span name="tfile" style="color: red;"></span>
									</div>
								</div>
								<div class="control-group">
									<label class="control-label" for="disabledInput">电子票背景原始图片：</label>
									<div class="controls">
										<image src="${routeForm.route.ticketpic}" style="width:320px;" />
									</div>
								</div>
								  <div class="control-group">
								<label class="control-label" for="focusedInput">免费线电子票文字</label>
								<div class="controls">
								    <input class="input-xlarge focused" name="ticketTitle"  maxlength='20' type="text" value="${routeForm.route.ticketTitle }">
								</div>
							  </div>
							    <div class="control-group">
								<label class="control-label" for="disabledInput">合作单位</label>
								<div class="controls">
								<select class="input-xlarge focused" name="belongId" id="belongId"  style="width: 280px;" >
									<option value="">未选择</option>
									<option value="1" 
									<c:if test="${routeForm.route.belongId==1}">
										selected="selected"
									</c:if>
									>易班路线</option>
								</select>
								<span style="color: #bd4247" id="routeStatusMsg"></span>
								</div>
							  </div>
							   <div class="control-group">
								<label class="control-label" for="disabledInput">路线集合号</label>
								<div class="controls">
								<input class="input-xlarge focused"  name="routeAggregateSign" id="routeAggregateSign" value="${routeForm.route.routeAggregateSign }" type="text">
								 <span style="color: #bd4247" id="aboutDistanceMsg"></span>
								</div>
							  </div>
							  <input type="hidden" name="isSubmit" value="1">
							  <div class="form-actions">
							    <button type="button" class="btn btn-primary" onclick="save(this)">保存</button>
								<button type="button" class="btn btn-primary" onclick="showModal('返回','您确定要离开此页面吗？','back()');">返回</button>
							  </div>
							</fieldset>
						  </form>
					</div>
				</div><!--/span-->
			</div><!--/row-->
                </div>
                <!--/span-->
            </div>
            <!--/row-->
            <!-- content ends -->
        </div>
        <!--/#content.span10-->
<%@ include file="/WEB-INF/jsp/inc/footer.jsp" %>
<script type="text/javascript">
	function checkRouteStatus(){
		if($("#routeStatus").val() == ""){
			$("#routeStatusMsg").html("请选择线路状态！");
			return false;
		}else{
			return true;
		}
	}
	function errorCheck() { 
		if(!$(".form-horizontal").validate() || !checkRouteStatus() || !checkAboutTime() || !checkAboutDistance() || !checkTicketPrice() || !checkoldPrice()){
			return false;
		}
		return true;
	}
	
	//校验大约时间
	function checkAboutTime() {
		var val = $("#aboutTime").val();
		if(val == "" || val == null){
			$("#aboutTimeMsg").html("请填写大约时间！");
			return false;
		}
		if(!/^[1-9][0-9]*$/.test(val)){
			$("#aboutTimeMsg").html("请填写整数！");
			return false;
		}else{
			$("#aboutTimeMsg").html("");
			return true;
		}
	}
	
	//校验大约距离
	function checkAboutDistance() {
		var val = $("#aboutDistance").val();
		if(val == "" || val == null){
			$("#aboutDistanceMsg").html("请填写大约距离！");
			return false;
		}
		if(!/^[1-9][0-9]*$/.test(val)){
			$("#aboutDistanceMsg").html("请填写整数！");
			return false;
		}else{
			$("#aboutDistanceMsg").html("");
			return true;
		}
	}
	function checkRouteType(){
		if($("#routeType").val() == ""){
			$("#routeTypeMsg").html("请选择线路类型！");
			return false;
		}else{
			return true;
		}
	}
	function checkTicketPrice(){
		var val = $("#ticketPrice").val();
		if(val == "" || val == null){
			$("#ticketPriceMsg").html("请填写票价！");
			return false;
		}
		reg=/^(([1-9]\d{0,9})|0)(\.\d{0,1})?$/;
		if(!reg.test(val)){
			$("#ticketPriceMsg").html("请填写数字，小数点后最多一位！");
			return false;
		}else{
			if(val.substring(val.length-1)=="."){
				$("#ticketPrice").val($("#ticketPrice").val()+"0");
			}
			$("#ticketPriceMsg").html("");
			return true;
		}
	}
	function save(src) {
		//防止重复提交
		src.disabled=true;
		if(!errorCheck()) {
			src.disabled=false;
			return false;
		}
		$('#myfrom').submit();		
	}
	
	function checkoldPrice(){
		var val = $("#oldPrice").val();
		if(val == "" || val == null){
			$("#oldPriceMsg").html("请填写票价！");
			return false;
		}
		reg=/^(([1-9]\d{0,9})|0)(\.\d{0,1})?$/;
		if(!reg.test(val)){
			$("#oldPriceMsg").html("请填写数字，小数点后最多一位！");
			return false;
		}else{
			if(val.substring(val.length-1)=="."){
				$("#oldPrice").val($("#oldPrice").val()+"0");
			}
			$("#oldPriceMsg").html("");
			return true;
		}
	}
</script>
</body>
</html>
