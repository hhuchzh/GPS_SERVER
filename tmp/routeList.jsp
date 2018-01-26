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
                        <h2><i class="icon-user"></i>路线管理xxxx</h2>
                    </div>
                    <br>                   
                    <div class="box-content">
               <form style="margin-left: 26px" id="myexcelsubmit" action="busgebus/route/excleImport"  enctype="multipart/form-data"  method="post" >           		                   		                    		                   
			    排班：            <input type="file" name ="file" id = "file"  />			                 
			                 <input type="button"  onclick="Importexcel()" 
			                value="导入Excel">
		           			<input type="hidden" id="msg" value="${msg}">
		         </form>
                    
                    	<form class="form-horizontal" name="myForm" action="<c:url value="busgebus/route/routeList" />" method="post" enctype="multipart/form-data">
                    	<fieldset>
                         <div style="padding-left: 15px; margin:-10px -10px 10px 10px;">
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
                                >免费线</option>
                         	</select>
	                     <button type="submit" class="btn btn-primary">查询</button>
	                     <input type="button" class="btn btn-primary"  onclick="addRoute()" value="添加路线">
	                    <input type="button" class="btn btn-primary" onclick="showRoutesInMap('')" value="查看所有地图路线">
	                    </div>
	                    <div style="height: 40px;margin-left: 25px;">
	                    	 请选择导出卖票情况的时期：
		                    <input class="laydate-icon" type="text" onclick="laydate({istime: false, format: 'YYYY-MM-DD'})" name="sendTimeString" id="sendTimeString"  value="" style="width: 150px;">~
		                    <input class="laydate-icon" type="text" onclick="laydate({istime: false, format: 'YYYY-MM-DD'})" name="sendTimeEnd" id="sendTimeEnd"  value="" style="width: 150px;">
		                    <input type="button" class="btn btn-primary" onclick="exportexcel()" value="导出所有路线卖票情况">
		                    <input type="button" class="btn btn-primary" onclick="exportShiftLocal()" value="导出所有班车轨迹">
		                    		                   
		         
		           
		           
	                    </div>
	                                                           
                        <table class="table table-striped table-bordered bootstrap-datatable">
                            <thead>
                            <tr>
                            	<th>路线ID</th>
                            	<th>所在城市</th>
                            	<th>路线名称</th>
                            	<th>起始地点</th>
								<th>结束地点</th>
								<th>路线状态</th>
								<th>路线类型</th>
								<th>票价</th>
								<th>原始票价</th>
								<th>大约时间</th>
								<th>大约距离</th>
								<th>创建时间</th>
								<th>集合标识</th>
								<th style="text-align: center;">操作</th>
                            </tr>
                            </thead>
                            <tbody>
                            <c:forEach var="item" items="${routeForm.routePage.result}">
	                            <tr>
	                            	<td>${item.routeId}</td>
	                            	<td>${item.region.regionName}</td>
	                            	<td>${item.routeName}</td>
	                            	<td>${item.startAddress}</td>
	                           		<td>${item.endAddress}</td>
	                            	<td>${item.routeStatus==0?"未开通":"开通"}</td>
	                            	<td>
	                            		<c:if test="${item.routeType==1}">班车线</c:if>
	                            		<c:if test="${item.routeType==2}">旅游线</c:if>
	                            		<c:if test="${item.routeType==3}">活动线</c:if>
	                            		<c:if test="${item.routeType==4}">企业线</c:if>
	                            		<c:if test="${item.routeType==5}">免费线</c:if>
	                            	</td>
	                            	<td>${item.ticketPrice}元</td>
	                            	<td>${empty item.oldPrice ? 0 : item.oldPrice}元</td>
	                            	<td>${item.aboutTime}</td>
	                            	<td>${item.aboutDistance}</td>	                
									<td>
										<fmt:formatDate value="${item.createTime}" pattern="yyyy-MM-dd HH:mm:ss"/>
									</td>
                                    <td>${item.routeAggregateSign}</td>>   
	                                <td class="center" align="center">
	                                	<a class="btn btn-success"" href="javascript:" onclick="editRoute('${item.routeId}')"><i class="icon-edit  icon-white"></i>修改路线</a>
	                                	<a class="btn btn-danger" href="javascript:showModal('删除','您确定删除该路线吗？','deleteRoute(${item.routeId})');"><i class="icon-trash icon-white"></i>删除路线</a>
	                                	<a class="btn btn-success" href="javascript:" onclick="viewClasses('${item.routeId}')"><i class="icon-zoom-in  icon-white"></i>查看班次</a>
	                                	<a class="btn btn-primary" href="javascript:" onclick="showRoutesInMap('${item.routeId}')"><i class="icon-zoom-in  icon-white"></i>查看地图路线</a>
	                                	<a class="btn btn-primary" href="javascript:" onclick="viewLocation('${item.routeId}')"><i class="icon-zoom-in  icon-white"></i>查看站点</a>
	                                	
	                                </td>
	                            </tr>
                            </c:forEach>
                            </tbody>
                        </table>
                        <div class="paginator" id="page" currentPage="${routeForm.routePage.cur}" totalPages="${routeForm.routePage.pageCount}" numberOfPages="5" onPageClicked="goPage" ></div>
                		<input id="currentPageNo" type="hidden" name="cur" value="${routeForm.routePage.cur}"/>
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
		document.forms[1].submit();
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
	
	function viewClasses(routeId){
		var form="<form action=\"busgebus/classes/classesList\" method=\"post\" name=\"viewForm\" id=\"viewForm\" style=\"display:none;\">";
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
	
	
	$(function(){
		if($("#msg").val()!=""){
			alert($("#msg").val());
		}
	});
	
	function Importexcel(){		
		  var filepath = $("#file").val();
		  if(filepath){
			  var re = /(\\+)/g; 
			  var filename = filepath.replace(re,"#"); 
			  //对路径字符串进行剪切截取 
			  var one = filename.split("#"); 
			  //获取数组中最后一个，即文件名 
			  var two = one[one.length-1]; 
			  //再对文件名进行截取，以取得后缀名 
			  var three = two.split("."); 
			   //获取截取的最后一个字符串，即为后缀名 
			  var last = three[three.length-1]; 
			  //添加需要判断的后缀名类型 
			  var tp = "xls,xlsx"; 
			  //返回符合条件的后缀名在字符串中的位置 
			  var rs = tp.indexOf(last); 				  
			  if(rs != -1){ 		
				  //src.disabled = true;
				  $('#myexcelsubmit').submit();		
			  }else{ 
					 alert("您选择的上传文件不是有效xls或者xlsx文件！","error");
			  		 return false; 
			  } 
		  }else{
			  alert('请选择Excel');
			  return;
		  }	
	}
	
	
</script>
</html>
