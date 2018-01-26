<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <%@include file="/WEB-INF/jsp/inc/base.jsp" %>
    <ry:binding parentCode="BUS_STATUS" bingdingName="busStatus"></ry:binding>
</head>
<body>
<%@include file="/WEB-INF/jsp/inc/header.jsp" %>
<div class="container-fluid">
    <div class="row-fluid">
        <%@include file="/WEB-INF/jsp/inc/left.jsp" %>
	<ry:binding type="3"></ry:binding>
        <div id="content" class="span10">
            <!-- content starts -->
            <div class="row-fluid">
                <div class="box span12">
                    <div class="box-header well" data-original-title>
                        <h2><i class="icon-user"></i>路线管理</h2>
                    </div>
                    <br>
                   
                    <div class="box-content">
                    	<form class="form-horizontal" name="myForm" action="<c:url value="busgebus/route/routeList" />" method="post">
                    	<fieldset>
                         <!--div style="padding-left: 15px; margin:-10px -10px 10px 10px;">
		                                                                关键字：<input class="input inline"  name="keyWord"  type="text" value="${routeForm.keyWord}" style="width: 10%;">
		                                                                路线状态 ：<select class="input inline" name="routeStatus" style="width: 10%;">
		                                  <option value="">全部</option>
		                                  <option value="0"
		                                  	<c:if test="${routeForm.route.routeStatus == 0 }">selected="selected"</c:if>
		                                   >未开通</option>
		                                  <option value="1"
		                                  	<c:if test="${routeForm.route.routeStatus == 1 }">selected="selected"</c:if>
		                                  >开通</option>
		                             </select>
		                                                            城市：
                         	<select name="cityCode" class="input inline" style="width: 10%;">
                         		<option value="-1"
                         			<c:if test="${routeForm.cityCode == '-1'}">selected="selected"</c:if>
                         		>全部</option>
                         		<c:forEach var="item" items="${regions}">
                         			<option value="${item.cityCode}" 
                         				<c:if test="${routeForm.cityCode == item.cityCode}">selected="selected"</c:if>
                         				<c:if test="${empty routeForm.cityCode && item.cityCode == '315'}">selected="selected"</c:if>
                         			>${item.regionName}</option>
                         		</c:forEach>
                         	</select>
                         	 路线类型：
                         	<select name="routeType" class="input inline" style="width: 10%;">
                         		<option value="-1"
                         			<c:if test="${routeForm.route.routeType == '-1'}">selected="selected"</c:if>
                         		>全部</option>
                         		<option value="1"
                                  	<c:if test="${routeForm.route.routeType == 1 || empty  routeForm.route.routeType}">selected="selected"</c:if>
                                >班车线</option>
                                <option value="2"
                               		<c:if test="${routeForm.route.routeType == 2 }">selected="selected"</c:if>
                                >旅游线</option>
                                <option value="3"
                               		<c:if test="${routeForm.route.routeType == 3 }">selected="selected"</c:if>
                                >活动线</option>
                                  <option value="4"
                               		<c:if test="${routeForm.route.routeType == 4 }">selected="selected"</c:if>
                                >企业线</option>
                                  <option value="5"
                               		<c:if test="${routeForm.route.routeType == 5 }">selected="selected"</c:if>
                                >企业及社会线</option>
                         	</select>
	                     <button type="submit" class="btn btn-primary">查询</button>
	                     <input type="button" class="btn btn-primary"  onclick="addRoute()" value="添加路线">
	                    <input type="button" class="btn btn-primary" onclick="showRoutesInMap('')" value="查看所有地图路线">
	                    </div -->
	                    <!--div style="height: 40px;margin-left: 25px;">
	                    	 请选择导出卖票情况的时期：
		                    <input class="laydate-icon" type="text" onclick="laydate({istime: false, format: 'YYYY-MM-DD'})" name="sendTimeString" id="sendTimeString"  value="" style="width: 150px;">~
		                    <input class="laydate-icon" type="text" onclick="laydate({istime: false, format: 'YYYY-MM-DD'})" name="sendTimeEnd" id="sendTimeEnd"  value="" style="width: 150px;">
		                    <input type="button" class="btn btn-primary" onclick="exportexcel()" value="导出所有路线卖票情况">
		                    <input type="button" class="btn btn-primary" onclick="exportShiftLocal()" value="导出所有班车轨迹">
	                    </div  -->
	                    <div style="height: 40px;margin-left: 25px;">
		                    <input type="button" class="btn btn-primary" onclick="addRouteAggregate()" value="添加标识">
	                    </div>
	                                                           
                        <table class="table table-striped table-bordered bootstrap-datatable">
                            <thead>
                            <tr>
                            	<th>路线集合ID</th>
                            	<th>路线集合标识</th>
								<th>创建时间</th>
								<th style="text-align: center;">操作</th>
                            </tr>
                            </thead>
                            <tbody>
                            <c:forEach var="item" items="${routeAggregateform.page.result}">
	                            <tr>
	                            	<td>${item.routeAggregateId}</td>
	                            	<td>${item.routeAggregateSign}</td>
									<td>
										<fmt:formatDate value="${item.createTime}" pattern="yyyy-MM-dd HH:mm:ss"/>
									</td>
                                       
	                                <td class="center" align="center">
	                                	<a class="btn btn-success" href="javascript:" onclick="viewClasses('${item.routeAggregateSign}')"><i class="icon-zoom-in  icon-white"></i>查看班次</a>
	                                </td>
	                            </tr>
                            </c:forEach>
                            </tbody>
                        </table>
                        <div class="paginator" id="page" currentPage="${routeAggregateform.page.cur}" totalPages="${routeAggregateform.page.pageCount}" numberOfPages="5" onPageClicked="goPage" ></div>
                		<input id="currentPageNo" type="hidden" name="cur" value="${routeAggregateform.page.cur}"/>
                		</fieldset>
                    	</form>
                    </div>
                </div>
                <div id="formDiv" style="display: none;"></div>
                <!--/span-->
				
            </div>
            <!--/row-->

            <!-- content ends -->
        </div>
        <!--/#content.span10-->

    </div>
</div>
<%@ include file="/WEB-INF/jsp/inc/footer.jsp" %>
</body>
<script type="text/javascript">
	
	
	function goPage(event,obj,type,page){
		if (obj.currentTarget.parentElement.className == "active")
            return;
		$("#currentPageNo").val(page);
		document.forms[0].submit();
	}
	//添加路线
	function addRoute(){
		location.href="<%=basePath%>busgebus/route/addRoute";
	}
	//编辑线路
	function editRoute(routeId){
		var form="<form action=\"busgebus/route/editRoute\" method=\"post\" name=\"editForm\" id=\"editForm\" style=\"display:none;\">";
		form += "<input type=\"hidden\" name=\"routeId\" value=\""+routeId+"\">";
		form += "<input type=\"hidden\" name=\"isSubmit\" value=\"0\">";
		form += "</form>";
		$("#formDiv").html(form);
		editForm.submit();
	}
	
	function deleteRoute(routeId){
		var form="<form action=\"busgebus/route/deleteRoute\" method=\"post\" name=\"deleteForm\"  style=\"display:none;\">";
		form += "<input type=\"hidden\" name=\"routeId\" value=\""+routeId+"\">";
		form += "</form>";
		$("#formDiv").html(form);
		deleteForm.submit();
	}
	
	function viewLocation(routeId){
		var form="<form action=\"busgebus/location/locationList\" method=\"post\" name=\"viewForm\" id=\"viewForm\" style=\"display:none;\">";
		form += "<input type=\"hidden\" name=\"routeId\" value=\""+routeId+"\">";
		form += "<input type=\"hidden\" name=\"isSubmit\" value=\"0\">";
		form += "<input type=\"hidden\" name=\"keyWord\" value=\""+$("input[name=keyWord]").val()+"\">";
		form += "<input type=\"hidden\" name=\"routeStatus\" value=\""+$("select[name=routeStatus]").val()+"\">";
		form += "<input type=\"hidden\" name=\"cityCode\" value=\""+$("select[name=cityCode]").val()+"\">";
		form += "<input type=\"hidden\" name=\"routeType\" value=\""+$("select[name=routeType]").val()+"\">";
		form += "<input type=\"hidden\" name=\"curPage\" value=\""+$("#currentPageNo").val()+"\">";
		form += "</form>";
		$("#formDiv").html(form);
		viewForm.submit();
	}
	
	function viewClasses(routeAggregateSign){
		var form="<form action=\"busgebus/route/queryAggregateRouteList\" method=\"post\" name=\"viewForm\" id=\"viewForm\" style=\"display:none;\">";
		form += "<input type=\"hidden\" name=\"routeAggregateSign\" value=\""+routeAggregateSign+"\">";
		form += "</form>";
		$("#formDiv").html(form);
		viewForm.submit();
	}
	
	function showRoutesInMap(routeId){
		var form="<form action=\"busgebus/route/showRouteListInMap\" target=\"_blank\" method=\"post\" name=\"viewForm\" id=\"viewForm\" style=\"display:none;\">";
		form += "<input type=\"hidden\" name=\"routeId\" value=\""+routeId+"\">";
		form += "</form>";
		$("#formDiv").html(form);
		viewForm.submit();
	}
	
	function exportexcel(){
		myForm.action="export/exportExcelAllRouteTicket";
		myForm.submit();
		myForm.action="busgebus/route/routeList";
	}
	function exportShiftLocal(){
		myForm.action="export/exportShiftLocal";
		myForm.submit();
		myForm.action="busgebus/route/routeList";
	}
	function addRouteAggregate(){
		var form="<form action=\"busgebus/routeAggregate/createRouteAggregate\" method=\"post\" name=\"viewForm\" id=\"viewForm\" style=\"display:none;\">";
		form += "<input type=\"hidden\" name=\"isSubmit\" value=\"0\">";
		form += "</form>";
		$("#formDiv").html(form);
		viewForm.submit();
	}
	
</script>
</html>
